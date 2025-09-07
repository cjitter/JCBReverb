#include "WaveformComponent.h"

//==============================================================================
WaveformComponent::WaveformComponent()
{
    // Iniciar timer para actualización suave a 30fps
    startTimerHz(30);
    
    // Inicializar buffers de historia de niveles
    inputLevels.resize(levelHistorySize, 0.0f);
    outputLevels.resize(levelHistorySize, 0.0f);
}

WaveformComponent::~WaveformComponent()
{
    stopTimer();
}

//==============================================================================
void WaveformComponent::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    const float width = static_cast<float>(bounds.getWidth());
    const float height = static_cast<float>(bounds.getHeight());
    
    // No dibujar fondo - dejar transparente
    
    // Dibujar línea base muy sutil
    g.setColour(Colours::gridLines.withAlpha(0.1f));
    g.drawHorizontalLine(static_cast<int>(height - 1), 0.0f, width);
    
    // Ancho de cada barra
    const float barWidth = width / static_cast<float>(levelHistorySize);
    
    // Dibujar historia de niveles
    {
        std::lock_guard<std::mutex> lock(dataLock);
        
        for (int i = 0; i < levelHistorySize; ++i)
        {
            // Calcular posición x (de izquierda a derecha, más nuevo a la derecha)
            int histIndex = (writePos - levelHistorySize + i + levelHistorySize) % levelHistorySize;
            float x = i * barWidth;
            
            // Obtener niveles
            float inputLevel = inputLevels[histIndex];
            float outputLevel = outputLevels[histIndex];
            
            // Calcular alturas usando toda la altura disponible
            float maxHeight = height * 0.95f;
            float inputHeight = inputLevel * maxHeight * (zoomEnabled ? 1.5f : 1.0f);
            float outputHeight = outputLevel * maxHeight * (zoomEnabled ? 1.5f : 1.0f);
            
            // Limitar alturas
            inputHeight = juce::jmin(inputHeight, height - 2.0f);
            outputHeight = juce::jmin(outputHeight, height - 2.0f);
            
            // Calcular opacidad basada en posición Y parámetros de reverb
            float normalizedPos = static_cast<float>(i) / static_cast<float>(levelHistorySize);
            
            // SIZE controla cuánto persiste el fade (más size = fade más largo)
            float fadeLength = 0.3f + reverbSize * 0.7f;
            float positionFade = std::pow(normalizedPos, 1.0f / fadeLength);
            
            // REFLECT controla la intensidad del fade
            float positionAlpha = positionFade * (0.4f + reflectAmount * 0.6f);
            
            // Dibujar barra de entrada (señal seca) - 45% del ancho
            if (inputHeight > 0.5f)
            {
                g.setColour(Colours::inputWaveform.withAlpha(positionAlpha * 0.5f));
                g.fillRect(x, height - inputHeight, barWidth * 0.45f, inputHeight);
            }
            
            // Dibujar barra de salida (con reverb) - 55% del ancho, ligeramente superpuesta
            if (outputHeight > 0.5f)
            {
                // Color más intenso donde hay más reverb (diferencia entre output e input)
                float reverbAmount = juce::jmax(0.0f, outputHeight - inputHeight) / maxHeight;
                float reverbAlpha = positionAlpha * (0.6f + reverbAmount * 0.4f);
                
                g.setColour(Colours::outputWaveform.withAlpha(reverbAlpha));
                g.fillRect(x + barWidth * 0.4f, height - outputHeight, barWidth * 0.55f, outputHeight);
                
                // Si hay mucha reverb, añadir un "glow" extra más visible
                if (reverbAmount > 0.05f)
                {
                    g.setColour(Colours::reverbTail.withAlpha(reverbAmount * positionAlpha * 0.4f));
                    g.fillRect(x - 1, height - outputHeight - 2, barWidth + 2, outputHeight + 2);
                }
            }
        }
        
        // Dibujar indicador de reverb actual (borde derecho)
        if (peakReverbLevel > 0.01f)
        {
            // Línea vertical que muestra la intensidad actual de reverb
            float reverbIndicatorHeight = peakReverbLevel * height * 0.8f;
            g.setColour(Colours::outputWaveform.withAlpha(0.8f));
            g.fillRect(width - 3.0f, height - reverbIndicatorHeight, 3.0f, reverbIndicatorHeight);
        }
    }
    
    // Dibujar texto indicador si hay reverb significativa
    if (currentOutputLevel > currentInputLevel * 1.2f)
    {
        g.setColour(Colours::outputWaveform.withAlpha(0.6f));
        g.setFont(10.0f);
        auto textBounds = bounds;
        g.drawText("REVERB", textBounds.removeFromTop(15), juce::Justification::topRight);
    }
}

void WaveformComponent::resized()
{
    // No hay componentes hijos que posicionar
}

//==============================================================================
void WaveformComponent::updateWaveformData(const std::vector<float>& inputSamples, 
                                          const std::vector<float>& processedSamples)
{
    // Usar try_lock para evitar bloquear el audio thread
    std::unique_lock<std::mutex> lock(dataLock, std::try_to_lock);
    if (!lock.owns_lock())
        return;
    
    // Calcular RMS de las muestras
    float inputRMS = 0.0f;
    float outputRMS = 0.0f;
    
    if (!inputSamples.empty())
    {
        for (const auto& sample : inputSamples)
            inputRMS += sample * sample;
        inputRMS = std::sqrt(inputRMS / static_cast<float>(inputSamples.size()));
    }
    
    if (!processedSamples.empty())
    {
        for (const auto& sample : processedSamples)
            outputRMS += sample * sample;
        outputRMS = std::sqrt(outputRMS / static_cast<float>(processedSamples.size()));
    }
    
    // Amplificar señales para mejor visualización
    const float visualGain = 8.0f;
    inputRMS *= visualGain;
    outputRMS *= visualGain;
    
    // Aplicar curva logarítmica para mejor respuesta visual
    inputRMS = std::log10(1.0f + inputRMS * 9.0f);  // Mapea a rango ~0-1
    outputRMS = std::log10(1.0f + outputRMS * 9.0f);
    
    // Suavizar los niveles
    const float attackTime = 0.1f;   // Respuesta rápida al ataque
    const float releaseTime = 0.95f; // Liberación lenta para ver la cola
    
    if (inputRMS > currentInputLevel)
        currentInputLevel = currentInputLevel * (1.0f - attackTime) + inputRMS * attackTime;
    else
        currentInputLevel = currentInputLevel * releaseTime + inputRMS * (1.0f - releaseTime);
        
    if (outputRMS > currentOutputLevel)
        currentOutputLevel = currentOutputLevel * (1.0f - attackTime) + outputRMS * attackTime;
    else
        currentOutputLevel = currentOutputLevel * releaseTime + outputRMS * (1.0f - releaseTime);
    
    // Calcular nivel de reverb (diferencia)
    float reverbLevel = juce::jmax(0.0f, currentOutputLevel - currentInputLevel);
    peakReverbLevel = peakReverbLevel * 0.9f + reverbLevel * 0.1f;
    
    // Guardar en historia
    inputLevels[writePos] = currentInputLevel;
    outputLevels[writePos] = currentOutputLevel;
    
    // Avanzar posición de escritura
    writePos = (writePos + 1) % levelHistorySize;
}

void WaveformComponent::setZoomEnabled(bool shouldZoom)
{
    if (zoomEnabled != shouldZoom)
    {
        zoomEnabled = shouldZoom;
        repaint();
    }
}

void WaveformComponent::timerCallback()
{
    // Repintar para actualizar visualización
    repaint();
}