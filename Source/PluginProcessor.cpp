//==============================================================================
//
//  Copyright 2025 Juan Carlos Blancas
//  This file is part of JCBReverb and is licensed under the GNU General Public License v3.0 or later.
//
//==============================================================================

//==============================================================================
// INCLUDES
//==============================================================================
// Archivos del proyecto
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Helpers/UTF8Helper.h"

//==============================================================================
// CONSTRUCTOR Y DESTRUCTOR
//==============================================================================
JCBReverbAudioProcessor::JCBReverbAudioProcessor()
    : juce::AudioProcessor(createBusesProperties()),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout()),  // nullptr = no automatic undo (proven solution tested on jr-granular)
      m_CurrentBufferSize(0),
      editorSize(1260, 360),
      lastPreset(0),
      currentProgram(-1)
{
    // Configurar límites del guiUndoManager para optimizar rendimiento
    guiUndoManager.setMaxNumberOfStoredUnits(0, 20); // Solo 20 transacciones exactas (ahorro de memoria)
    
    
    // Inicializar Gen~ state
    m_PluginState = (CommonState *)JCBReverb::create(44100, 64);
    JCBReverb::reset(m_PluginState);

    // Inicializar buffers de Gen~
    m_InputBuffers = new t_sample *[JCBReverb::num_inputs()];
    m_OutputBuffers = new t_sample *[JCBReverb::num_outputs()];
    
    for (int i = 0; i < JCBReverb::num_inputs(); i++) {
        m_InputBuffers[i] = nullptr;
    }
    for (int i = 0; i < JCBReverb::num_outputs(); i++) {
        m_OutputBuffers[i] = nullptr;
    }

    // Vincular listeners de parámetros de gen~ a APVTS
    for (int i = 0; i < JCBReverb::num_params(); i++)
    {
        auto name = juce::String(JCBReverb::getparametername(m_PluginState, i));
        apvts.addParameterListener(name, this);
    }
    
    // IMPORTANTE: Sincronizar valores iniciales con Gen~ usando IDs reales del export
    // Cualquier parámetro de Gen cuyo ID exista en el APVTS se envía tal cual; no aplicar validaciones legacy.
    for (int i = 0; i < JCBReverb::num_params(); ++i)
    {
        auto id = juce::String(JCBReverb::getparametername(m_PluginState, i));
        if (auto* p = apvts.getRawParameterValue(id))
        {
            float v = p->load();
            JCBReverb::setparameter(m_PluginState, i, v, nullptr);
        }
    }

    // DISTORTION: No requiere parámetro AAX de gain reduction
    // Los distorsionadores no tienen reducción dinámica de ganancia como limitadores/maximizadores
}

JCBReverbAudioProcessor::~JCBReverbAudioProcessor()
{
    // CRÍTICO: Primero indicar que estamos destruyendo para evitar race conditions
    isBeingDestroyed = true;
    
    // Detener timer AAX inmediatamente (antes que cualquier otra cosa)
    #if JucePlugin_Build_AAX
    stopTimer();
    // Pequeña espera para asegurar que el timer callback no esté ejecutándose
    juce::Thread::sleep(10);
    #endif
    
    // Destruir listeners de parámetros del apvts
    for (int i = 0; i < JCBReverb::num_params(); i++)
    {
        auto name = juce::String(JCBReverb::getparametername(m_PluginState, i));
        apvts.removeParameterListener(name, this);
    }
    
    // Limpiar buffers con protección nullptr
    if (m_InputBuffers != nullptr) {
        for (int i = 0; i < JCBReverb::num_inputs(); i++) {
            if (m_InputBuffers[i] != nullptr) {
                delete[] m_InputBuffers[i];
                m_InputBuffers[i] = nullptr;
            }
        }
        delete[] m_InputBuffers;
        m_InputBuffers = nullptr;
    }
    
    if (m_OutputBuffers != nullptr) {
        for (int i = 0; i < JCBReverb::num_outputs(); i++) {
            if (m_OutputBuffers[i] != nullptr) {
                delete[] m_OutputBuffers[i];
                m_OutputBuffers[i] = nullptr;
            }
        }
        delete[] m_OutputBuffers;
        m_OutputBuffers = nullptr;
    }
    
    // Destruir Gen~ state al final
    if (m_PluginState != nullptr) {
        JCBReverb::destroy(m_PluginState);
        m_PluginState = nullptr;
    }
}

//==============================================================================
// MÉTODOS PRINCIPALES DEL AUDIOPROCESSOR
//==============================================================================
void JCBReverbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Configuración de canales en modo debug eliminada para release
    
    // Inicializar sample rate y vector size y RESETEAR el estado de Gen
    m_PluginState->sr = sampleRate;
    m_PluginState->vs = samplesPerBlock;
    JCBReverb::reset(m_PluginState);
    
    // Callbacks para visualización se añadirán cuando se implemente el display de reverb
    
    // Pre-asignar buffers con tamaño máximo esperado para evitar allocations en audio thread
    // Usar un tamaño seguro que cubra la mayoría de casos (4096 samples es común máximo)
    const long maxExpectedBufferSize = juce::jmax(static_cast<long>(samplesPerBlock), 4096L);
    assureBufferSize(maxExpectedBufferSize);
    
    // Pre-asignar vectors de waveform data para evitar resize en audio thread
    {
        std::lock_guard<std::mutex> lock(waveformMutex);
        const size_t maxWaveformSize = static_cast<size_t>(maxExpectedBufferSize);
        currentInputSamples.resize(maxWaveformSize);
        currentProcessedSamples.resize(maxWaveformSize);
    }

    // 3) ***Clave***: sincroniza SR/VS con Gen y re-dimensiona sus delays/constantes
    //    Esto asegura que Gen use el sampleRate real del host (48k si el proyecto es 48k)
    JCBReverb::reset (m_PluginState);

    // Cachear indices de gen para evitar bucles por nombre
    genIdxLookahead = genIdxBypass = -1;
    for (int i = 0; i < JCBReverb::num_params(); ++i)
    {
        const char* raw = JCBReverb::getparametername(m_PluginState, i);
        juce::String name(raw ? raw : "");
        if (name == "p_BYPASS")    genIdxBypass   = i; // por si te hace falta en futuro
    }

    // DISTORTION: Latencia mínima fija - no necesita lookahead variable
    setLatencySamples(0);
    
    // === INICIALIZACIÓN DEL SISTEMA DE BYPASS SUAVE ===
    // Pre-asignar scratch buffers para evitar allocations en audio thread
    ensureScratchCapacity(juce::jmax(static_cast<int>(samplesPerBlock), 4096));
    
    // Configurar longitud del fade desde bypassFadeMs (7ms por defecto)
    {
        const int lenFromMs = juce::roundToInt(bypassFadeMs * static_cast<float>(sampleRate) / 1000.0f);
        bypassFadeLen = juce::jlimit(128, 512, lenFromMs > 0 ? lenFromMs : 128);
    }
    bypassFadePos = 0;
    
    // Estado inicial coherente con el host
    const bool hb = isHostBypassed();
    hostBypassMirror.store(hb, std::memory_order_relaxed);
    bypassState = hb ? BypassState::Bypassed : BypassState::Active;
    lastWantsBypass = hb;

    // Initialize atomic meter values
    // CRITICAL: Changed from SmoothedValue to atomic - no reset() needed
    leftInputRMS.store(-100.0f, std::memory_order_relaxed);
    rightInputRMS.store(-100.0f, std::memory_order_relaxed);
    
    leftOutputRMS.store(-100.0f, std::memory_order_relaxed);
    rightOutputRMS.store(-100.0f, std::memory_order_relaxed);
    
    
    
    // leftSC.store(-100.0f, std::memory_order_relaxed);
    // rightSC.store(-100.0f, std::memory_order_relaxed);
    
    // Configurar buffers auxiliares
    
    trimInputBuffer.setSize(2, samplesPerBlock);
    trimInputBuffer.clear();
    
    // sidechainBuffer.setSize(getTotalNumInputChannels(), samplesPerBlock);
    // sidechainBuffer.clear();
    
    // Inicializar buffers de forma de onda
    currentInputSamples.resize(samplesPerBlock, 0.0f);
    currentProcessedSamples.resize(samplesPerBlock, 0.0f);
    
    // IMPORTANTE: Re-sincronizar todos los parámetros con Gen~ tras el reset
    for (int i = 0; i < JCBReverb::num_params(); ++i)
    {
        auto id = juce::String(JCBReverb::getparametername(m_PluginState, i));
        if (auto* p = apvts.getRawParameterValue(id))
            JCBReverb::setparameter(m_PluginState, i, p->load(), nullptr);
    }
}

void JCBReverbAudioProcessor::releaseResources()
{
    // Limpiar buffers auxiliares
    trimInputBuffer.setSize(0, 0);
    // sidechainBuffer.setSize(0, 0);
}

//==============================================================================
// PROCESAMIENTO DE AUDIO
//==============================================================================
void JCBReverbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    processBlockCommon(buffer, /*hostWantsBypass*/ false);
}

void JCBReverbAudioProcessor::processBlockBypassed(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    processBlockCommon(buffer, /*hostWantsBypass*/ true);
}

void JCBReverbAudioProcessor::processBlockCommon(juce::AudioBuffer<float>& buffer, bool hostWantsBypass)
{
    juce::ScopedNoDenormals noDenormals;
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    
    // Ajustar buffers auxiliares si es necesario
    assureBufferSize(numSamples);
    
    // === 1. SIEMPRE capturar entrada ANTES de procesar (crítico para bypass) ===
    ensureScratchCapacity(numSamples);
    float* inL = scratchIn.getWritePointer(0);
    float* inR = scratchIn.getWritePointer(1);
    {
        const float* srcL = buffer.getReadPointer(0);
        const float* srcR = (numChannels > 1) ? buffer.getReadPointer(1) : srcL;
        std::memcpy(inL, srcL, sizeof(float) * static_cast<size_t>(numSamples));
        if (numChannels > 1) 
            std::memcpy(inR, srcR, sizeof(float) * static_cast<size_t>(numSamples));
        else
            std::memcpy(inR, inL, sizeof(float) * static_cast<size_t>(numSamples));
    }
    
    // === 2. Procesar WET con Gen~ (siempre activo, f_BYPASS interno manejado por Gen~) ===
    fillGenInputBuffers(buffer);
    processGenAudio(numSamples);
    fillOutputBuffers(buffer); // buffer = WET procesado
    
    auto* wetL = buffer.getWritePointer(0);
    auto* wetR = (numChannels > 1) ? buffer.getWritePointer(1) : wetL;
    
    // === 3. DRY sin compensación (JCBDistortion no tiene latencia/lookahead) ===
    float* dryL = scratchDry.getWritePointer(0);
    float* dryR = scratchDry.getWritePointer(1);
    // DRY = entrada capturada (sin delay porque no hay latencia)
    for (int n = 0; n < numSamples; ++n) {
        dryL[n] = inL[n];
        if (numChannels > 1) 
            dryR[n] = inR[n];
    }
    
    // === 4. FSM de Bypass y mezcla equal-power (como JCBCompressor) ===
    const bool wantsBypass = hostWantsBypass;
    hostBypassMirror.store(wantsBypass, std::memory_order_relaxed);
    const bool bypassEdge = (wantsBypass != lastWantsBypass);
    lastWantsBypass = wantsBypass;
    
    // Transiciones de estado en flancos (al inicio del bloque)
    switch (bypassState)
    {
        case BypassState::Active:
            if (bypassEdge && wantsBypass) {
                bypassState = BypassState::FadingToBypass;
                bypassFadePos = 0;
            }
            break;
            
        case BypassState::Bypassed:
            if (bypassEdge && !wantsBypass) {
                bypassState = BypassState::FadingToActive;
                bypassFadePos = 0;
            }
            break;
            
        case BypassState::FadingToBypass:
            if (bypassEdge && !wantsBypass) {
                // Revertir fade en curso
                bypassState = BypassState::FadingToActive;
                bypassFadePos = juce::jmax(0, bypassFadeLen - bypassFadePos);
            }
            break;
            
        case BypassState::FadingToActive:
            if (bypassEdge && wantsBypass) {
                // Revertir fade en curso
                bypassState = BypassState::FadingToBypass;
                bypassFadePos = juce::jmax(0, bypassFadeLen - bypassFadePos);
            }
            break;
    }
    
    // === 5. Aplicar estado o fade ===
    const bool fading = (bypassState == BypassState::FadingToBypass || 
                         bypassState == BypassState::FadingToActive);
    
    if (!fading)
    {
        // Estados estables
        if (bypassState == BypassState::Active)
        {
            // WET tal cual (ya está en buffer)
        }
        else // Bypassed
        {
            for (int n = 0; n < numSamples; ++n) {
                wetL[n] = dryL[n];
                if (numChannels > 1) wetR[n] = dryR[n];
            }
        }
    }
    else
    {
        // === Fade con detección de cruce por cero (como JCBCompressor) ===
        int fadeStartOffset = 0;
        const bool startingFadeThisBlock = 
            ((bypassEdge && wantsBypass && bypassState == BypassState::FadingToBypass) ||
             (bypassEdge && !wantsBypass && bypassState == BypassState::FadingToActive)) &&
            (bypassFadePos == 0);
        
        if (startingFadeThisBlock)
        {
            // Buscar cruce por cero en primeras 32 muestras
            const float* refL = (bypassState == BypassState::FadingToBypass) ? dryL : wetL;
            const float* refR = (numChannels > 1) ?
                               ((bypassState == BypassState::FadingToBypass) ? dryR : wetR) : refL;
            
            auto nearZero = [](float x) noexcept { return std::abs(x) < 1.0e-5f; };
            const int searchMax = juce::jmin(32, numSamples - 1);
            
            for (int i = 1; i <= searchMax; ++i)
            {
                const float l0 = refL[i-1], l1 = refL[i];
                const float r0 = refR[i-1], r1 = refR[i];
                const bool zcL = (nearZero(l0) || nearZero(l1) || (l0 * l1 <= 0.0f));
                const bool zcR = (nearZero(r0) || nearZero(r1) || (r0 * r1 <= 0.0f));
                if (zcL || zcR) {
                    fadeStartOffset = i;
                    break;
                }
            }
        }
        
        // Aplicar fade con ventana Hann
        for (int n = 0; n < numSamples; ++n)
        {
            float wWet = 0.0f, wDry = 0.0f;
            
            // Antes del offset, mantener pesos fijos
            if (n < fadeStartOffset)
            {
                if (bypassState == BypassState::FadingToBypass) {
                    wWet = 1.0f; wDry = 0.0f;
                } else {
                    wWet = 0.0f; wDry = 1.0f;
                }
                const float outL = wWet * wetL[n] + wDry * dryL[n];
                const float outR = wWet * wetR[n] + wDry * (numChannels > 1 ? dryR[n] : dryL[n]);
                wetL[n] = outL;
                if (numChannels > 1) wetR[n] = outR;
                continue;
            }
            
            // Calcular pesos del fade
            const float t = juce::jlimit(0.0f, 1.0f,
                                         static_cast<float>(bypassFadePos) / 
                                         static_cast<float>(juce::jmax(1, bypassFadeLen)));
            
            // Ventana Hann (sin²/cos²) para mantener amplitud estable
            const float s = std::sin(t * juce::MathConstants<float>::halfPi);
            const float c = std::cos(t * juce::MathConstants<float>::halfPi);
            
            if (bypassState == BypassState::FadingToBypass) {
                wWet = c * c;  // cos² (de 1 a 0)
                wDry = s * s;  // sin² (de 0 a 1)
            } else {
                wWet = s * s;  // sin² (de 0 a 1)
                wDry = c * c;  // cos² (de 1 a 0)
            }
            
            const float outL = wWet * wetL[n] + wDry * dryL[n];
            const float outR = wWet * wetR[n] + wDry * (numChannels > 1 ? dryR[n] : dryL[n]);
            wetL[n] = outL;
            if (numChannels > 1) wetR[n] = outR;
            
            // Avanzar fade
            ++bypassFadePos;
            if (bypassFadePos >= bypassFadeLen)
            {
                bypassState = (bypassState == BypassState::FadingToBypass) ? 
                             BypassState::Bypassed : BypassState::Active;
                
                // Resto del bloque ya en estado final
                if (bypassState == BypassState::Bypassed) {
                    for (int k = n + 1; k < numSamples; ++k) {
                        wetL[k] = dryL[k];
                        if (numChannels > 1) wetR[k] = dryR[k];
                    }
                }
                // Si Active, WET ya está correcto
                break;
            }
        }
    }
    
    // === 6. Análisis y medición post-procesamiento ===
    
    // Alimentar visualización cuando se implemente el display de reverb
    
    // Capturar formas de onda
    captureInputWaveformData(buffer, numSamples);
    captureOutputWaveformData(numSamples);
    
    // Actualizar detección de clipping
    updateClipDetection(buffer, buffer);
    
    // Actualizar medidores
    updateInputMeters(buffer);
    updateOutputMeters(buffer);
}

//==============================================================================
// INTEGRACIÓN GEN~
//==============================================================================

/**
 * Asegurar que los buffers de Gen~ tengan el tamaño correcto
 * CRÍTICO: Esta función gestiona la memoria dinámica para la comunicación con el motor DSP Gen~
 * AUDIO-THREAD SAFE: Solo redimensiona si es absolutamente necesario para evitar RT violations
 */
void JCBReverbAudioProcessor::assureBufferSize(long bufferSize)
{
    if (bufferSize > m_CurrentBufferSize) {
        // NOTA: RT-safe porque prepareToPlay() pre-asigna hasta 4096 samples
        // Solo se ejecuta este bloque si el DAW solicita > 4096 samples (muy raro)
        
        // Redimensionar buffers de entrada
        for (int i = 0; i < JCBReverb::num_inputs(); i++) {
            delete[] m_InputBuffers[i];
            m_InputBuffers[i] = new t_sample[bufferSize];
        }
        
        // Redimensionar buffers de salida
        for (int i = 0; i < JCBReverb::num_outputs(); i++) {
            delete[] m_OutputBuffers[i];
            m_OutputBuffers[i] = new t_sample[bufferSize];
        }
        
        m_CurrentBufferSize = bufferSize;
    }
}

void JCBReverbAudioProcessor::fillGenInputBuffers(const juce::AudioBuffer<float>& buffer)
{
    const auto mainInputChannels = getMainBusNumInputChannels();
    const int numSamples = buffer.getNumSamples();
    
    if (mainInputChannels > 1) {
        // Modo estéreo - fill main L/R inputs (inputs 0 and 1)
        for (int j = 0; j < numSamples; j++) {
            m_InputBuffers[0][j] = buffer.getReadPointer(0)[j];  // L
            m_InputBuffers[1][j] = buffer.getReadPointer(1)[j];  // R
        }
    } else {
        // Modo mono - duplicar señal mono a ambos canales L/R para procesamiento stereo-linked
        if (mainInputChannels == 1) {
            for (int j = 0; j < numSamples; j++) {
                m_InputBuffers[0][j] = buffer.getReadPointer(0)[j];  // L = mono
                m_InputBuffers[1][j] = buffer.getReadPointer(0)[j];  // R = mono (duplicado)
            }
        }
    }
}

void JCBReverbAudioProcessor::processGenAudio(int numSamples)
{
    JCBReverb::perform(m_PluginState,
                          m_InputBuffers,
                          JCBReverb::num_inputs(),
                          m_OutputBuffers,
                          JCBReverb::num_outputs(),
                          numSamples);
}

void JCBReverbAudioProcessor::fillOutputBuffers(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const auto mainOutputChannels = getMainBusNumOutputChannels();
    
    // Llenar buffers de salida principales - conversión double a float
    for (int i = 0; i < mainOutputChannels; i++) {
        float* destPtr = buffer.getWritePointer(i);
        const t_sample* srcPtr = m_OutputBuffers[i];
        for (int j = 0; j < numSamples; j++) {
            destPtr[j] = static_cast<float>(srcPtr[j]);
        }
    }
    
    // Preparar buffer para medidor de entrada (post-TRIM): usar outs 4 y 5 de Gen si existen
    // Notas de convención:
    // - out1/out2: main L/R
    // - out4/out5 (1-based) => índices [3]/[4] (0-based): post-TRIM IN L/R
    if (JCBReverb::num_outputs() > 4)
    {
        float* trimL = trimInputBuffer.getWritePointer(0);
        const t_sample* srcL = m_OutputBuffers[3];
        for (int j = 0; j < numSamples; j++)
            trimL[j] = static_cast<float>(srcL[j]);

        if (trimInputBuffer.getNumChannels() > 1)
        {
            float* trimR = trimInputBuffer.getWritePointer(1);
            const t_sample* srcR = m_OutputBuffers[4];
            for (int j = 0; j < numSamples; j++)
                trimR[j] = static_cast<float>(srcR[j]);
        }
    }
    else
    {
        // Fallback: usar la entrada capturada si aún no están exportadas las salidas post-TRIM
        const int trimChans = trimInputBuffer.getNumChannels();
        const float* inSrcL = scratchIn.getReadPointer(0);
        float* trimL = trimInputBuffer.getWritePointer(0);
        std::memcpy(trimL, inSrcL, sizeof(float) * static_cast<size_t>(numSamples));
        if (trimChans > 1)
        {
            const float* inSrcR = scratchIn.getReadPointer(1);
            float* trimR = trimInputBuffer.getWritePointer(1);
            std::memcpy(trimR, inSrcR, sizeof(float) * static_cast<size_t>(numSamples));
        }
    }
}

//==============================================================================
// MEDIDORES DE AUDIO
//==============================================================================
void JCBReverbAudioProcessor::updateInputMeters(const juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const auto mainInputChannels = getMainBusNumInputChannels();

    // Calcular valores RMS
    const auto rmsValueL = juce::Decibels::gainToDecibels(trimInputBuffer.getRMSLevel(0, 0, numSamples));
    const auto rmsValueR = (trimInputBuffer.getNumChannels() > 1) ?
    juce::Decibels::gainToDecibels(trimInputBuffer.getRMSLevel(1, 0, numSamples)) : rmsValueL;
    
    // Calcular valores de pico reales
    const auto peakValueL = juce::Decibels::gainToDecibels(trimInputBuffer.getMagnitude(0, 0, numSamples));
    const auto peakValueR = (trimInputBuffer.getNumChannels() > 1) ?
    juce::Decibels::gainToDecibels(trimInputBuffer.getMagnitude(1, 0, numSamples)) : peakValueL;
    
    // Usar combinación ponderada 70% peak + 30% RMS
    const auto displayValueL = (peakValueL * 0.7f) + (rmsValueL * 0.3f);
    const auto displayValueR = (peakValueR * 0.7f) + (rmsValueR * 0.3f);
    
    // Si estamos cerca del clipping (> -3dB), mostrar el valor de pico puro
    const auto inputValueL = (peakValueL > -3.0f) ? peakValueL : displayValueL;
    const auto inputValueR = (peakValueR > -3.0f) ? peakValueR : displayValueR;
    
    // CRÍTICO: Usar atomic store para thread safety
    // No smoothing is done here - just direct atomic updates
    if (mainInputChannels < 2) {
        // Modo mono - ambos medidores muestran el mismo valor
        leftInputRMS.store(inputValueL, std::memory_order_relaxed);
        rightInputRMS.store(inputValueL, std::memory_order_relaxed);
    } else {
        // Modo estéreo - medidores independientes
        leftInputRMS.store(inputValueL, std::memory_order_relaxed);
        rightInputRMS.store(inputValueR, std::memory_order_relaxed);
    }
}

void JCBReverbAudioProcessor::updateOutputMeters(const juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const auto mainOutputChannels = getMainBusNumOutputChannels();

    // Calcular valores RMS para el medidor (promedio de potencia)
    const auto rmsValueL = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, numSamples));
    const auto rmsValueR = (mainOutputChannels > 1) ?
    juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, numSamples)) : rmsValueL;
    
    // Calcular valores de pico reales (máximo absoluto en el buffer)
    const auto peakValueL = juce::Decibels::gainToDecibels(buffer.getMagnitude(0, 0, numSamples));
    const auto peakValueR = (mainOutputChannels > 1) ?
    juce::Decibels::gainToDecibels(buffer.getMagnitude(1, 0, numSamples)) : peakValueL;
    
    // Usar una combinación ponderada de RMS y Peak para mejor visualización
    // 70% peak + 30% RMS da una representación más precisa similar a medidores profesionales
    const auto displayValueL = (peakValueL * 0.7f) + (rmsValueL * 0.3f);
    const auto displayValueR = (peakValueR * 0.7f) + (rmsValueR * 0.3f);
    
    // Si estamos cerca del clipping (> -3dB), mostrar el valor de pico puro
    const auto finalValueL = (peakValueL > -3.0f) ? peakValueL : displayValueL;
    const auto finalValueR = (peakValueR > -3.0f) ? peakValueR : displayValueR;
    
    // CRÍTICO: Usar atomic store para thread safety
    if (mainOutputChannels > 1) {
        // Modo estéreo
        leftOutputRMS.store(finalValueL, std::memory_order_relaxed);
        rightOutputRMS.store(finalValueR, std::memory_order_relaxed);
    } else {
        // Modo mono
        leftOutputRMS.store(finalValueL, std::memory_order_relaxed);
        rightOutputRMS.store(finalValueL, std::memory_order_relaxed);
    }
}

// Los distorsionadores no tienen reducción dinámica de ganancia

/*
void JCBReverbAudioProcessor::updateSidechainMeters(const juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();

    // Resetear flags de clipping sidechain para este buffer
    bool scClip[2] = {false, false};
    
    const bool extKeyActive = false;  // Maximizer no tiene external key
    
    // Si EXT KEY no está activo, mostrar silencio en los medidores
    if (!extKeyActive) {
        const auto valueSC = -100.0f;
        
        // leftSC.store(valueSC, std::memory_order_relaxed);
        // rightSC.store(valueSC, std::memory_order_relaxed);
        
        return;  // No procesar más si EXT KEY está desactivado
    }
    
    // CAMBIO: Usar las salidas 5 y 6 de Gen~ (índices 5 y 6 en m_OutputBuffers)
    // Estas salidas ya incluyen el procesamiento de SC TRIM aplicado por Gen~
    if (JCBReverb::num_outputs() > 6) {
        // Calcular RMS y pico del sidechain desde las salidas de Gen~
        float maxSCL = 0.0f, maxSCR = 0.0f;
        float rmsSumL = 0.0f, rmsSumR = 0.0f;
        
        for (int i = 0; i < numSamples; ++i) {
            // Usar salidas 5 y 6 de Gen~ que ya tienen SC TRIM aplicado
            float sampleL = static_cast<float>(m_OutputBuffers[5][i]);
            float sampleR = static_cast<float>(m_OutputBuffers[6][i]);
            
            // Peak detection
            maxSCL = juce::jmax(maxSCL, std::abs(sampleL));
            maxSCR = juce::jmax(maxSCR, std::abs(sampleR));
            
            // RMS accumulation
            rmsSumL += sampleL * sampleL;
            rmsSumR += sampleR * sampleR;
        }
        
        // Calcular RMS
        float rmsL = std::sqrt(rmsSumL / static_cast<float>(numSamples));
        float rmsR = std::sqrt(rmsSumR / static_cast<float>(numSamples));
        
        const auto rmsValueSCLeft = juce::Decibels::gainToDecibels(rmsL);
        const auto rmsValueSCRight = juce::Decibels::gainToDecibels(rmsR);
        const auto peakValueSCLeft = juce::Decibels::gainToDecibels(maxSCL);
        const auto peakValueSCRight = juce::Decibels::gainToDecibels(maxSCR);
        
        // Detectar clipping basado en el valor de pico
        if (maxSCL >= 0.999f) {  // Usar el mismo umbral que los medidores principales
            scClip[0] = true;
        }
        if (maxSCR >= 0.999f) {
            scClip[1] = true;
        }
        
        // Usar combinación ponderada como en los medidores principales
        const auto displayValueSCLeft = (peakValueSCLeft * 0.7f) + (rmsValueSCLeft * 0.3f);
        const auto displayValueSCRight = (peakValueSCRight * 0.7f) + (rmsValueSCRight * 0.3f);
        
        const auto valueSCLeft = (peakValueSCLeft > -3.0f) ? peakValueSCLeft : displayValueSCLeft;
        const auto valueSCRight = (peakValueSCRight > -3.0f) ? peakValueSCRight : displayValueSCRight;
        
        // if (!isProTools()) {
        //     leftSC.store(valueSCLeft, std::memory_order_relaxed);
        //     rightSC.store(valueSCRight, std::memory_order_relaxed);
        // } else {
        //     // ProTools: usar solo canal izquierdo para ambos medidores
        //     leftSC.store(valueSCLeft, std::memory_order_relaxed);
        //     leftSC.store(valueSCLeft, std::memory_order_relaxed);
        // }
    } else {
        // Sidechain no disponible - mostrar silencio
        const auto valueSC = -100.0f;
        
        // leftSC.store(valueSC, std::memory_order_relaxed);
        // rightSC.store(valueSC, std::memory_order_relaxed);
    }
    
    // Actualizar flags atómicos de clip
    for (int channel = 0; channel < 2; ++channel) {
        if (scClip[channel]) {
            sidechainClipDetected[channel] = true;
        }
    }
}
*/

//==============================================================================
// CONFIGURACIÓN DE BUSES Y PARÁMETROS
//==============================================================================
juce::AudioProcessor::BusesProperties JCBReverbAudioProcessor::createBusesProperties()
{
    auto propBuses = juce::AudioProcessor::BusesProperties()
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        .withInput("Input", juce::AudioChannelSet::stereo(), true);
    
    /*
    juce::PluginHostType daw;
    
    if (daw.isProTools())
        propBuses.addBus(true, "Sidechain MONO", juce::AudioChannelSet::mono(), false);
    else
        propBuses.addBus(true, "Sidechain ST", juce::AudioChannelSet::stereo(), false);
    */
    
    return propBuses;
}

// Validación de configuraciones de canales - define qué layouts acepta el plugin
bool JCBReverbAudioProcessor::isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // Verificar bus principal de salida
    auto mainOut = layouts.getMainOutputChannelSet();
    if (mainOut != juce::AudioChannelSet::mono()
        && mainOut != juce::AudioChannelSet::stereo())
        return false;
    
    // Verificar bus principal de entrada
    auto mainIn = layouts.getMainInputChannelSet();
    if (mainIn != juce::AudioChannelSet::mono()
        && mainIn != juce::AudioChannelSet::stereo())
        return false;
    
    // Pro Tools AAX: Rechazar específicamente stereo input → mono output
    // Solo permitir: 1→1, 2→2, 1→2. NO permitir: 2→1
#if JucePlugin_Build_AAX
    // En formato AAX, rechazar siempre stereo input → mono output
    if (mainIn == juce::AudioChannelSet::stereo() && mainOut == juce::AudioChannelSet::mono())
        return false;
#endif
    
    /*
    // Si hay bus de sidechain, verificar que sea válido
    if (layouts.inputBuses.size() > 1)
    {
        auto sidechainBus = layouts.inputBuses[1];
        
        // El sidechain puede estar desactivado (empty)
        if (!sidechainBus.isDisabled())
        {
            // Solo aceptar sidechain mono o estéreo si está activo
            if (sidechainBus != juce::AudioChannelSet::mono() 
                && sidechainBus != juce::AudioChannelSet::stereo())
                return false;
        }
            
        // No aceptar más de 2 buses de entrada
        if (layouts.inputBuses.size() > 2)
            return false;
    }
    */
    
    return true;
#endif
}

/**
 * Crear el layout de parámetros del plugin
 * CRÍTICO: Define todos los parámetros del compresor en orden alfabético
 * Incluye configuración de rangos, valores por defecto y metadata para cada parámetro
 * Version hint 21 fuerza re-escaneo en hosts para parámetros renombrados
 */
juce::AudioProcessorValueTreeState::ParameterLayout JCBReverbAudioProcessor::createParameterLayout()
{
   const int versionHint = 1;  // Nueva versión para JCBReverb
   std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

   // === PARÁMETROS DEL REVERB ===
   
   // a_INPUT - Input gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("a_INPUT", versionHint),
       "Input",
       juce::NormalisableRange<float>(-12.f, 12.f, 0.1f),
       0.f,
       "dB"));

   // b_DRYWET - Dry/Wet mix
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("b_DRYWET", versionHint),
       "Dry/Wet",
       juce::NormalisableRange<float>(0.f, 1.f, 0.01f),
       0.33f,
       "%",
       juce::AudioParameterFloat::genericParameter,
       [](float value, int) { return juce::String(static_cast<int>(value * 100)) + "%"; },
       nullptr));

   // c_REFLECT - Reflections
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("c_REFLECT", versionHint),
       "Reflections",
       juce::NormalisableRange<float>(0.1f, 0.98f, 0.001f),
       0.86f));

   // d_DAMP - Damping
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("d_DAMP", versionHint),
       "Damping",
       juce::NormalisableRange<float>(0.f, 1.f, 0.01f),
       0.8f));

   // e_SIZE - Room size
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("e_SIZE", versionHint),
       "Size",
       juce::NormalisableRange<float>(0.1f, 4.f, 0.001f),
       1.0f));

   // f_ST - Stereo width
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("f_ST", versionHint),
       "Stereo",
       juce::NormalisableRange<float>(0.f, 0.8f, 0.001f),
       0.5f));

   // g_FREEZE - Freeze mode
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("g_FREEZE", versionHint),
       "Freeze",
       false));

   // === PARÁMETROS DEL EQ ===
   
   // h_LOWGAIN - Low shelf gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("h_LOWGAIN", versionHint),
       "Low Gain",
       juce::NormalisableRange<float>(-12.f, 12.f, 0.1f),
       0.f,
       "dB"));

   // i_PEAKGAIN - Peak gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("i_PEAKGAIN", versionHint),
       "Peak Gain",
       juce::NormalisableRange<float>(-12.f, 12.f, 0.1f),
       0.f,
       "dB"));

   // j_HIGAIN - High shelf gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("j_HIGAIN", versionHint),
       "High Gain",
       juce::NormalisableRange<float>(-12.f, 12.f, 0.1f),
       0.f,
       "dB"));

   // k_LPF - Low pass filter
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("k_LPF", versionHint),
       "LPF",
        juce::NormalisableRange<float>(100.f, 20000.f, 1.f, 0.3f),
        20000.f,
       "Hz"));

   // l_HPF - High pass filter
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("l_HPF", versionHint),
       "HPF",
       juce::NormalisableRange<float>(20.f, 5000.f, 1.f, 0.3f),
       20.f,
       "Hz"));

   // m_OUTPUT - Output gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("m_OUTPUT", versionHint),
       "Output",
       juce::NormalisableRange<float>(-12.f, 12.f, 0.1f),
       0.f,
       "dB"));

   // n_LOWFREQ - Low shelf frequency
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("n_LOWFREQ", versionHint),
       "Low Freq",
       juce::NormalisableRange<float>(20.f, 800.f, 1.f, 0.3f),
       500.f,
       "Hz"));

   // o_PEAKFREQ - Peak frequency
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("o_PEAKFREQ", versionHint),
       "Peak Freq",
       juce::NormalisableRange<float>(100.f, 2500.f, 1.f, 0.3f),
       800.f,
       "Hz"));

   // p_HIFREQ - High shelf frequency
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("p_HIFREQ", versionHint),
       "High Freq",
       juce::NormalisableRange<float>(800.f, 15000.f, 1.f, 0.3f),
       2000.f,
       "Hz"));

   // q_ONOFFEQ - EQ on/off
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("q_ONOFFEQ", versionHint),
       "EQ",
       false));

   // === PARÁMETROS DEL COMPRESOR ===
   
   // r_ONOFFCOMP - Compressor on/off
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("r_ONOFFCOMP", versionHint),
       "Comp",
       false));

   // s_THD - Threshold
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("s_THD", versionHint),
       "Threshold",
       juce::NormalisableRange<float>(-36.f, 0.f, 0.1f),
       -12.f,
       "dB"));

   // t_RATIO - Ratio
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("t_RATIO", versionHint),
       "Ratio",
       juce::NormalisableRange<float>(1.f, 20.f, 0.1f),
       2.f,
       ":1"));

   // u_ATK - Attack
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("u_ATK", versionHint),
       "Attack",
       juce::NormalisableRange<float>(5.f, 250.f, 0.1f, 0.3f),
       10.f,
       "ms"));

   // v_REL - Release
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("v_REL", versionHint),
       "Release",
       juce::NormalisableRange<float>(5.f, 500.f, 1.f, 0.3f),
       100.f,
       "ms"));

   // w_MAKEUP - Makeup gain
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("w_MAKEUP", versionHint),
       "Makeup",
       juce::NormalisableRange<float>(-6.f, 6.f, 0.1f),
       0.f,
       "dB"));

   // x_PREPOST - PRE/POST switch
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("x_PREPOST", versionHint),
       "Pre/Post",
       false));

   // y_IOMODE - IO layout mode (1=mono->mono, 2=mono->stereo, 3=stereo->stereo)
   params.push_back(std::make_unique<juce::AudioParameterFloat>(
       juce::ParameterID("y_IOMODE", versionHint),
       "IO Mode",
       juce::NormalisableRange<float>(1.f, 3.f, 1.f),
       3.f));

   // z_SOFTCLIP - Softclip enable
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("z_SOFTCLIP", versionHint),
       "Softclip",
       false));

   // === PARÁMETRO DE BYPASS (para el host) ===
   params.push_back(std::make_unique<juce::AudioParameterBool>(
       juce::ParameterID("bypass", versionHint),
       "Bypass",
       false));

   return { params.begin(), params.end() };
}

//==============================================================================
// GESTIÓN DE PARÁMETROS
//==============================================================================
void JCBReverbAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    // Por ahora, mapeo simple de parámetros JUCE a índices Gen~
    // Los parámetros del reverb en Gen~ van de 0 a 22
    
    if (!m_PluginState) return;
    
    // Mapear IDs de parámetros a índices Gen~
    int genParamIndex = -1;
    
    // Parámetros del reverb
    if (parameterID == "a_INPUT") genParamIndex = 0;
    else if (parameterID == "b_DRYWET") genParamIndex = 1;
    else if (parameterID == "c_REFLECT") genParamIndex = 2;
    else if (parameterID == "d_DAMP") genParamIndex = 3;
    else if (parameterID == "e_SIZE") genParamIndex = 4;
    else if (parameterID == "f_ST") genParamIndex = 5;
    else if (parameterID == "g_FREEZE") genParamIndex = 6;
    
    // Parámetros del EQ
    else if (parameterID == "h_LOWGAIN") genParamIndex = 7;
    else if (parameterID == "i_PEAKGAIN") genParamIndex = 8;
    else if (parameterID == "j_HIGAIN") genParamIndex = 9;
    else if (parameterID == "k_LPF") genParamIndex = 10;
    else if (parameterID == "l_HPF") genParamIndex = 11;
    else if (parameterID == "m_OUTPUT") genParamIndex = 12;
    else if (parameterID == "n_LOWFREQ") genParamIndex = 13;
    else if (parameterID == "o_PEAKFREQ") genParamIndex = 14;
    else if (parameterID == "p_HIFREQ") genParamIndex = 15;
    else if (parameterID == "q_ONOFFEQ") genParamIndex = 16;
    
    // Parámetros del compresor
    else if (parameterID == "r_ONOFFCOMP") genParamIndex = 17;
    else if (parameterID == "s_THD") genParamIndex = 18;
    else if (parameterID == "t_RATIO") genParamIndex = 19;
    else if (parameterID == "u_ATK") genParamIndex = 20;
    else if (parameterID == "v_REL") genParamIndex = 21;
    else if (parameterID == "w_MAKEUP") genParamIndex = 22;

    // Extensiones de reverb
    else if (parameterID == "x_PREPOST") genParamIndex = 23;
    else if (parameterID == "y_IOMODE") genParamIndex = 24;
    else if (parameterID == "z_SOFTCLIP") genParamIndex = 25;
    
    // Si encontramos el parámetro, actualizarlo en Gen~
    if (genParamIndex >= 0)
    {
        // Convertir de valor normalizado JUCE a valor real para Gen~
        if (auto* param = apvts.getParameter(parameterID))
        {
            float denormalizedValue = param->convertFrom0to1(param->convertTo0to1(newValue));
            JCBReverb::setparameter(m_PluginState, genParamIndex, denormalizedValue, nullptr);
        }
    }
    
    // Bypass es manejado por el host, no por Gen~
    if (parameterID == "bypass")
    {
        // El bypass se maneja en processBlock
    }
}
//==============================================================================
// Métodos de programa (presets)
int JCBReverbAudioProcessor::getNumPrograms()
{
    return 0; // 3 antes, añadir 1 por comportamiento extraño algunos hosts
}

int JCBReverbAudioProcessor::getCurrentProgram()
{
    return currentProgram;
}

void JCBReverbAudioProcessor::setCurrentProgram(int index)
{
    currentProgram = index;
}

const juce::String JCBReverbAudioProcessor::getProgramName(int index)
{
    return juce::String();
}

void JCBReverbAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
    // No implementado - los nombres de preset son fijos
}

//==============================================================================
// Métodos de medidores
float JCBReverbAudioProcessor::getRmsInputValue(const int channel) const noexcept
{
    // CRASH FIX: Safety check - return safe value if not initialized
    if (!isInitialized()) {
        return -100.0f;  // Safe default value
    }
    
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return leftInputRMS.load(std::memory_order_relaxed);
    if (channel == 1)
        return rightInputRMS.load(std::memory_order_relaxed);
    return -100.0f;  // Return -100dB for invalid channels
}

float JCBReverbAudioProcessor::getRmsOutputValue(const int channel) const noexcept
{
    // CRASH FIX: Safety check - return safe value if not initialized
    if (!isInitialized()) {
        return -100.0f;  // Safe default value
    }
    
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return leftOutputRMS.load(std::memory_order_relaxed);
    if (channel == 1)
        return rightOutputRMS.load(std::memory_order_relaxed);
    return -100.0f;  // Return -100dB for invalid channels
}

// DISTORTION: No requiere función getGainReductionValue - eliminada
// Los distorsionadores no tienen gain reduction

/*
float JCBReverbAudioProcessor::getSCValue(const int channel) const noexcept
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return leftSC.load(std::memory_order_relaxed);
    if (channel == 1)
        return rightSC.load(std::memory_order_relaxed);
    return -100.0f;  // Return -100dB for invalid channels
}
*/

//==============================================================================
// Utilidades
bool JCBReverbAudioProcessor::isProTools() const noexcept
{
    juce::PluginHostType daw;
    return daw.isProTools();
}

juce::String JCBReverbAudioProcessor::getPluginFormat() const noexcept
{
    // Detectar el formato del plugin en tiempo de ejecución
    const auto format = juce::PluginHostType().getPluginLoadedAs();
    
    switch (format)
    {
        case juce::AudioProcessor::wrapperType_VST3:
            return "VST3";
        case juce::AudioProcessor::wrapperType_AudioUnit:
            return "AU";
        case juce::AudioProcessor::wrapperType_AudioUnitv3:
            return "AUv3";
        case juce::AudioProcessor::wrapperType_AAX:
            return "AAX";
        case juce::AudioProcessor::wrapperType_VST:
            return "VST2";
        case juce::AudioProcessor::wrapperType_Standalone:
            return "Standalone";
        default:
            return "";
    }
}


//==============================================================================
// CAPTURA DE DATOS PARA VISUALIZACIÓN DE ENVOLVENTES
//==============================================================================
void JCBReverbAudioProcessor::captureInputWaveformData(const juce::AudioBuffer<float>& inputBuffer, int numSamples)
{
    // AUDIO-THREAD SAFE: Usar try_lock para evitar bloquear el audio thread
    std::unique_lock<std::mutex> lock(waveformMutex, std::try_to_lock);
    if (!lock.owns_lock()) {
        // Si no puede obtener el lock, salir inmediatamente para evitar RT violations
        return;
    }
    
    // AUDIO-THREAD SAFE: Usar tamaño fijo pre-asignado, no resize() dinámico
    if (currentInputSamples.size() < static_cast<size_t>(numSamples)) {
        // Solo redimensionar si es absolutamente necesario (debería estar pre-asignado)
        currentInputSamples.resize(juce::jmax(numSamples, 4096));
    }
    
    // Para la visualización de entrada, preferir outs post-TRIM (Gen out4/out5 => idx [3]/[4]) si existen
    if (JCBReverb::num_outputs() > 4)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            currentInputSamples[i] = static_cast<float>((m_OutputBuffers[3][i] + m_OutputBuffers[4][i]) * 0.5);
        }
    }
    else
    {
        // Fallback: usar el buffer de entrada del host
        const int chs = inputBuffer.getNumChannels();
        if (chs > 1)
        {
            for (int i = 0; i < numSamples; ++i)
                currentInputSamples[i] = 0.5f * (inputBuffer.getReadPointer(0)[i] + inputBuffer.getReadPointer(1)[i]);
        }
        else
        {
            const float* src = inputBuffer.getReadPointer(0);
            std::memcpy(currentInputSamples.data(), src, sizeof(float) * static_cast<size_t>(numSamples));
        }
    }
}

void JCBReverbAudioProcessor::captureOutputWaveformData(int numSamples)
{
    // AUDIO-THREAD SAFE: Usar try_lock para evitar bloquear el audio thread
    std::unique_lock<std::mutex> lock(waveformMutex, std::try_to_lock);
    if (!lock.owns_lock()) {
        // Si no puede obtener el lock, salir inmediatamente para evitar RT violations
        return;
    }
    
    // AUDIO-THREAD SAFE: Usar tamaño fijo pre-asignado, no resize() dinámico
    if (currentProcessedSamples.size() < static_cast<size_t>(numSamples)) {
        currentProcessedSamples.resize(juce::jmax(numSamples, 4096));
    }
    
    // Copiar salida procesada (promedio de canales principales L/R)
    for (int i = 0; i < numSamples; ++i)
    {
        currentProcessedSamples[i] = (m_OutputBuffers[0][i] + m_OutputBuffers[1][i]) * 0.5f;
        
        // DISTORTION: No acceder a salida 3 Gen~ - no hay gain reduction
    }
}

void JCBReverbAudioProcessor::getWaveformData(std::vector<float>& inputSamples, std::vector<float>& processedSamples) const
{
    std::lock_guard<std::mutex> lock(waveformMutex);
    inputSamples = currentInputSamples;
    processedSamples = currentProcessedSamples;
}

// DISTORTION: getWaveformDataWithGR eliminada - no hay gain reduction

// DISTORTION: No requiere función getMaxGainReduction - eliminada
// Los distorsionadores no tienen gain reduction


bool JCBReverbAudioProcessor::isPlaybackActive() const noexcept
{
    // Siempre activo para decay permanente como plugins profesionales
    return true;
}


//==============================================================================
// GESTIÓN DEL EDITOR
//==============================================================================
juce::AudioProcessorEditor* JCBReverbAudioProcessor::createEditor()
{
    return new JCBReverbAudioProcessorEditor(*this, guiUndoManager);
}


//==============================================================================
// SERIALIZACIÓN DEL ESTADO
//==============================================================================
void JCBReverbAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Crear una copia del state para no modificar el original
    auto stateCopy = apvts.state.createCopy();
    
    // Remover parámetros momentáneos antes de guardar
    // Estos botones no deben persistir entre sesiones
    auto paramsNode = stateCopy.getChildWithName("PARAMETERS");
    if (paramsNode.isValid()) {
        // No persistir el bypass del host en el estado
        auto param = paramsNode.getChildWithProperty("id", "bypass");
        if (param.isValid())
            param.setProperty("value", 0.0f, nullptr);
        
        // DISTORTION: Plugin completamente limpio de parámetros legacy
    }
    
    auto preset = stateCopy.getOrCreateChildWithName("Presets", nullptr);
    preset.setProperty("currentPresetID", lastPreset, nullptr);
    preset.setProperty("tooltipEnabled", tooltipEnabled, nullptr);
    preset.setProperty("presetDisplayText", presetDisplayText, nullptr);
    preset.setProperty("presetTextItalic", presetTextItalic, nullptr);
    preset.setProperty("envelopeVisualEnabled", envelopeVisualEnabled, nullptr);
    preset.setProperty("tooltipLanguageEnglish", tooltipLanguageEnglish, nullptr);
    
    // Guardar tamaño del editor
    preset.setProperty("editorWidth", editorSize.x, nullptr);
    preset.setProperty("editorHeight", editorSize.y, nullptr);
    
    // Guardar estado del modo de visualización (no automatizable)
    preset.setProperty("displayModeIsFFT", displayModeIsFFT, nullptr);
    
    // Save A/B states
    auto abNode = stateCopy.getOrCreateChildWithName("ABStates", nullptr);
    abNode.setProperty("isStateA", isStateA, nullptr);
    
    // Save state A
    auto stateANode = abNode.getOrCreateChildWithName("StateA", nullptr);
    stateANode.removeAllChildren(nullptr);
    for (const auto& [paramId, value] : stateA.values) {
        stateANode.setProperty(paramId, value, nullptr);
    }
    
    // Save state B
    auto stateBNode = abNode.getOrCreateChildWithName("StateB", nullptr);
    stateBNode.removeAllChildren(nullptr);
    for (const auto& [paramId, value] : stateB.values) {
        stateBNode.setProperty(paramId, value, nullptr);
    }
    
    juce::MemoryOutputStream memoria(destData, true);
    stateCopy.writeToStream(memoria);
}

void JCBReverbAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        apvts.state = tree;
        
        // Forzar parámetros momentáneos a OFF después de cargar
        if (auto* pBypass = apvts.getParameter("bypass"))
            pBypass->setValueNotifyingHost(0.0f);
        
        // Re-sincronizar todos los parámetros a Gen tras cargar estado
        if (m_PluginState)
        {
            for (int i = 0; i < JCBReverb::num_params(); ++i)
            {
                auto id = juce::String(JCBReverb::getparametername(m_PluginState, i));
                if (auto* p = apvts.getRawParameterValue(id))
                    JCBReverb::setparameter(m_PluginState, i, p->load(), nullptr);
            }
        }
        
        // Clear undo history AFTER all values have been set
        // This prevents any parameter changes from being recorded in undo history
        guiUndoManager.clearUndoHistory();
        
        auto preset = apvts.state.getChildWithName("Presets");
        if (preset.isValid()) {
            lastPreset = preset.getProperty("currentPresetID");
            tooltipEnabled = preset.getProperty("tooltipEnabled");
            presetDisplayText = preset.getProperty("presetDisplayText", "DEFAULT");
            presetTextItalic = preset.getProperty("presetTextItalic", false);
            envelopeVisualEnabled = preset.getProperty("envelopeVisualEnabled", true);
            tooltipLanguageEnglish = preset.getProperty("tooltipLanguageEnglish", false);
            
            // Restaurar tamaño del editor
            int savedWidth = preset.getProperty("editorWidth", 1250);
            int savedHeight = preset.getProperty("editorHeight", 350);
            editorSize = {savedWidth, savedHeight};
            
            // Restaurar estado del modo de visualización (no automatizable)
            displayModeIsFFT = preset.getProperty("displayModeIsFFT", false);
        }
        
        // Restore A/B states
        auto abNode = apvts.state.getChildWithName("ABStates");
        if (abNode.isValid()) {
            isStateA = abNode.getProperty("isStateA", true);
            
            // Restore state A
            auto stateANode = abNode.getChildWithName("StateA");
            if (stateANode.isValid()) {
                stateA.values.clear();
                for (int i = 0; i < stateANode.getNumProperties(); ++i) {
                    auto propName = stateANode.getPropertyName(i);
                    stateA.values[propName.toString()] = stateANode[propName];
                }
            }
            
            // Restore state B
            auto stateBNode = abNode.getChildWithName("StateB");
            if (stateBNode.isValid()) {
                stateB.values.clear();
                for (int i = 0; i < stateBNode.getNumProperties(); ++i) {
                    auto propName = stateBNode.getPropertyName(i);
                    stateB.values[propName.toString()] = stateBNode[propName];
                }
            }
        }
        
        // IMPORTANTE: Sincronizar todos los parámetros con Gen~ después de cargar el estado
        for (int i = 0; i < JCBReverb::num_params(); i++) {
            auto paramName = juce::String(JCBReverb::getparametername(m_PluginState, i));
            if (auto* param = apvts.getRawParameterValue(paramName)) {
                float value = param->load();
                
                // Corregir valores muy pequeños en ATK y REL
                if (paramName == "d_ATK") {
                    if (value < 0.1f) {
                        value = 0.1f;
                        // Actualizar el parámetro en el APVTS
                        if (auto* audioParam = apvts.getParameter(paramName)) {
                            audioParam->setValueNotifyingHost(audioParam->convertTo0to1(value));
                        }
                    }
                }
                if (paramName == "e_REL") {
                    if (value < 0.1f) {
                        value = 0.1f;
                        // Actualizar el parámetro en el APVTS
                        if (auto* audioParam = apvts.getParameter(paramName)) {
                            audioParam->setValueNotifyingHost(audioParam->convertTo0to1(value));
                        }
                    }
                }
                // NOTA: El compresor no tiene parámetro HOLD (es del expansor/gate)
                
                parameterChanged(paramName, value);
            }
        }
        
        
        // Forzar actualización del editor de forma thread-safe
        // Usar MessageManager para evitar llamadas directas a getActiveEditor()
        juce::MessageManager::callAsync([this]() {
            if (auto* editor = dynamic_cast<JCBReverbAudioProcessorEditor*>(getActiveEditor())) {
                // El editor necesita actualizar la función de transferencia
                editor->updateTransferFunctionFromProcessor();
            }
        });
    }
}

//==============================================================================
// COMPARACIÓN A/B
//==============================================================================
void JCBReverbAudioProcessor::saveCurrentStateToActive() 
{
    if (isStateA) {
        stateA.captureFrom(apvts);
    } else {
        stateB.captureFrom(apvts);
    }
}

void JCBReverbAudioProcessor::toggleAB() 
{
    // Save current state before switching
    saveCurrentStateToActive();
    
    // Switch state
    isStateA = !isStateA;
    
    // Load the other state
    if (isStateA) {
        stateA.applyTo(apvts);
    } else {
        stateB.applyTo(apvts);
    }
}

void JCBReverbAudioProcessor::copyAtoB() 
{
    stateA.captureFrom(apvts);
    stateB = stateA;
}

void JCBReverbAudioProcessor::copyBtoA() 
{
    stateB.captureFrom(apvts);
    stateA = stateB;
}


//==============================================================================
// MÉTODOS LEGACY
//==============================================================================
int JCBReverbAudioProcessor::getNumParameters()
{
    // Retornar el número real de parámetros del juce::AudioProcessor
    // que incluye los de Gen~ más cualquier parámetro adicional (como AAX gain reduction)
    return static_cast<int>(getParameters().size());
}

float JCBReverbAudioProcessor::getParameter(int index)
{
    // Verificar si el índice está dentro del rango de Gen~
    if (index < JCBReverb::num_params())
    {
        t_param value;
        t_param min = JCBReverb::getparametermin(m_PluginState, index);
        t_param range = fabs(JCBReverb::getparametermax(m_PluginState, index) - min);
        
        JCBReverb::getparameter(m_PluginState, index, &value);
        
        value = (value - min) / range;
        
        return value;
    }
    else
    {
        // Manejar parámetros adicionales (como AAX gain reduction)
        // Para el parámetro de gain reduction, devolver 0.0 (sin reducción)
        return 0.0f;
    }
}

void JCBReverbAudioProcessor::setParameter(int index, float newValue)
{
    // Verificar si el índice está dentro del rango de Gen~
    if (index < JCBReverb::num_params())
    {
        t_param min = JCBReverb::getparametermin(m_PluginState, index);
        t_param range = fabs(JCBReverb::getparametermax(m_PluginState, index) - min);
        t_param value = newValue * range + min;
        
        JCBReverb::setparameter(m_PluginState, index, value, nullptr);
    }
    else
    {
        // Manejar parámetros adicionales (como AAX gain reduction)
        // El parámetro de gain reduction es de solo lectura, no hacer nada
    }
}

const juce::String JCBReverbAudioProcessor::getParameterName(int index)
{
    // Verificar si el índice está dentro del rango de Gen~
    if (index < JCBReverb::num_params())
    {
        return juce::String(JCBReverb::getparametername(m_PluginState, index));
    }
    else
    {
        // Manejar parámetros adicionales (como AAX gain reduction)
        #if JucePlugin_Build_AAX
        if (index == JCBReverb::num_params()) // Índice 25 para AAX
        {
            return "Gain Reduction";
        }
        #endif
        return "";
    }
}

const juce::String JCBReverbAudioProcessor::getParameterText(int index)
{
    // Método legacy para compatibilidad con hosts - algunos DAWs pueden llamarlo
    if (index >= 0 && index < JCBReverb::num_params())
    {
        juce::String text = juce::String(getParameter(index));
        text += juce::String(" ");
        text += juce::String(JCBReverb::getparameterunits(m_PluginState, index));
        return text;
    }
    
    // Retornar string vacío para índices inválidos
    return "";
}

const juce::String JCBReverbAudioProcessor::getInputChannelName(int channelIndex) const
{
    return juce::String(channelIndex + 1);
}

const juce::String JCBReverbAudioProcessor::getOutputChannelName(int channelIndex) const
{
    return juce::String(channelIndex + 1);
}

bool JCBReverbAudioProcessor::isInputChannelStereoPair(int index) const
{
    if (isProTools())
    {
        if (getMainBusNumInputChannels() > 1)
            return JCBReverb::num_inputs() == 4;
        else
            return false;
    }
    else
        return JCBReverb::num_inputs() == 4;
}

bool JCBReverbAudioProcessor::isOutputChannelStereoPair(int index) const
{
    return JCBReverb::num_outputs() == 2;
}


//==============================================================================
// Clip Detection Methods
//==============================================================================

void JCBReverbAudioProcessor::updateClipDetection(const juce::AudioBuffer<float>& inputBuffer, const juce::AudioBuffer<float>& outputBuffer)
{
    const int numSamples = inputBuffer.getNumSamples();
    const auto mainInputChannels = getMainBusNumInputChannels();
    const auto mainOutputChannels = getMainBusNumOutputChannels();
    
    // NOTA: El compresor no tiene soft clip, siempre detectar clips en salida
    bool isSoftClipActive = false; // Compresor no tiene soft clip
    
    // Reset clip flags for this buffer
    bool inputClip[2] = {false, false};
    bool outputClip[2] = {false, false};
    
    // Detectar clips en entrada (usando trimInputBuffer para consistencia con medidores)
    for (int channel = 0; channel < juce::jmin(2, mainInputChannels); ++channel) {
        for (int sample = 0; sample < numSamples; ++sample) {
            if (channel < trimInputBuffer.getNumChannels()) {
                float value = std::abs(trimInputBuffer.getSample(channel, sample));
                if (value >= 0.999f) {  // Umbral de clip ligeramente por debajo de 1.0
                    inputClip[channel] = true;
                    break;  // Solo necesitamos detectar un clip por buffer
                }
            }
        }
    }
    
    // Detectar clips en salida solo si soft clip NO está activo
    if (!isSoftClipActive) {
        for (int channel = 0; channel < juce::jmin(2, mainOutputChannels); ++channel) {
            for (int sample = 0; sample < numSamples; ++sample) {
                float value = std::abs(outputBuffer.getSample(channel, sample));
                if (value >= 0.999f) {  // Umbral de clip ligeramente por debajo de 1.0
                    outputClip[channel] = true;
                    break;  // Solo necesitamos detectar un clip por buffer
                }
            }
        }
    }
    
    // Actualizar flags atómicos
    for (int channel = 0; channel < 2; ++channel) {
        if (inputClip[channel]) {
            inputClipDetected[channel] = true;
        }
        if (outputClip[channel]) {
            outputClipDetected[channel] = true;
        }
    }
}

bool JCBReverbAudioProcessor::getInputClipDetected(const int channel) const noexcept
{
    jassert(channel == 0 || channel == 1);
    if (channel >= 0 && channel < 2) {
        return inputClipDetected[channel].load();
    }
    return false;
}

bool JCBReverbAudioProcessor::getOutputClipDetected(const int channel) const noexcept
{
    jassert(channel == 0 || channel == 1);
    if (channel >= 0 && channel < 2) {
        return outputClipDetected[channel].load();
    }
    return false;
}

/*
bool JCBReverbAudioProcessor::getSidechainClipDetected(const int channel) const noexcept
{
    jassert(channel == 0 || channel == 1);
    if (channel >= 0 && channel < 2) {
        return sidechainClipDetected[channel].load();
    }
    return false;
}
*/

void JCBReverbAudioProcessor::resetClipIndicators()
{
    for (int channel = 0; channel < 2; ++channel) {
        inputClipDetected[channel] = false;
        outputClipDetected[channel] = false;
        // sidechainClipDetected[channel] = false;
    }
}

// DISTORTION: No requiere función getGainReductionForHost - eliminada
// Los distorsionadores no tienen gain reduction

//==============================================================================
// Timer implementation
// Los distorsionadores no tienen parámetros AAX de gain reduction

//==============================================================================
// Format-specific implementations

// DISTORTION: No requiere función AAX getAAXMeterValue - eliminada
// Los distorsionadores no tienen medidores de gain reduction

#if JucePlugin_Build_VST3
void JCBReverbAudioProcessor::updateVST3GainReduction()
{
    // Para VST3, necesitaríamos acceso al IEditController
    // Esto se haría típicamente en el wrapper VST3
    // Por ahora solo preparamos el método
}
#endif

//==============================================================================
// TIMER CALLBACK
//==============================================================================
void JCBReverbAudioProcessor::timerCallback()
{
    // Timer callback para tareas que requieren ejecución fuera del audio thread
    // Para distorsión, mantenemos funcionalidad mínima necesaria
    
    // Verificar si el processor está siendo destruido
    if (isBeingDestroyed.load()) {
        return;
    }
    
    // Actualizar estado de playback para medidores
    // En distorsión no necesitamos lógica compleja de gain reduction
}

//==============================================================================
// FACTORY FUNCTION DEL PLUGIN
//==============================================================================

/**
 * Función factory requerida por JUCE
 * CRÍTICO: Punto de entrada que utilizan los hosts (DAWs) para crear instancias del plugin
 * Esta función es llamada automáticamente por el framework JUCE cuando:
 * - El DAW carga el plugin por primera vez
 * - Se crea una nueva instancia del plugin en el proyecto
 * - Se duplica una pista que contiene el plugin
 */
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JCBReverbAudioProcessor();
}
