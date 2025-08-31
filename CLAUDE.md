# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

---

**IMPORTANT:** This project documentation is primarily in Spanish as it's developed for Spanish-speaking educational context. The following guidelines should be followed exactly.

---

## 🧭 Project Overview

**JCBReverb** es un plugin de audio (VST3, AU, AAX) basado en **JUCE** y un motor DSP exportado desde **gen~ (Max/MSP)**. Es un procesador de reverberación estéreo tipo Freeverb con EQ paramétrico de 5 bandas y compresor integrado.

### Características principales:
- **23 parámetros completamente implementados** desde Gen~
- **Reverb estéreo** con control de reflexiones, damping y tamaño de sala
- **EQ paramétrico de 5 bandas** (Low Shelf, Peak, High Shelf)
- **Compresor dinámico** con threshold, ratio, attack, release y makeup
- **Freeze mode** para efectos especiales
- **Control Dry/Wet** independiente
- **Input/Output gain** con control preciso
- **Filtros HPF/LPF** para modelado tonal

---

## ⚠️ CLion + Ninja como entorno principal

- El proyecto se desarrolla en **CLion** con generador **Ninja**.
- **No usar `cmake` sin `-G Ninja`** desde terminal, salvo para pruebas controladas.
- **No contaminar `cmake-build-release`** con Makefiles o Xcode.
- Usar carpetas separadas para pruebas alternativas (`build-xcode`, etc.).
- CLion controla la compilación: respetar sus configuraciones.

### Scripts manuales
Hay scripts para builds finales que se ejecutan manualmente. No automatizar ni modificar:

- `build-xcode-aax-release.sh`
- `build-xcode-vst3-au-release.sh`
- `build-xcode-vst3_script.sh`
- `build-xcode-au_script.sh`

---

## ⚠️⚠️⚠️ SECCIÓN CRÍTICA: THREAD SAFETY ⚠️⚠️⚠️

### 🔴 ADVERTENCIA FUNDAMENTAL
**El desarrollo de plugins de audio requiere estricto cumplimiento de thread safety. Violaciones pueden causar crashes en DAWs.**

### REGLAS ABSOLUTAS - NUNCA VIOLAR:
1. **NUNCA** llamar `repaint()`, `setVisible()`, `setBounds()` o cualquier método GUI desde `parameterChanged()`
2. **NUNCA** asumir thread safety - si hay duda, NO es thread-safe
3. **SIEMPRE** usar `MessageManager::callAsync()` con `SafePointer` para actualizaciones GUI desde audio thread
4. **SIEMPRE** verificar CADA listener de parámetros línea por línea

### Checklist OBLIGATORIO antes de afirmar "es thread-safe":
- [ ] ¿He revisado TODOS los `parameterChanged()` en el proyecto?
- [ ] ¿He verificado que NO hay llamadas directas a GUI desde audio thread?
- [ ] ¿He confirmado uso de `std::atomic<>` para variables compartidas?
- [ ] ¿He verificado `SafePointer` en TODOS los lambdas?
- [ ] ¿He probado con automatización agresiva en DAW?

### 📖 Documentación obligatoria:
**Si existe `THREAD_SAFETY_GUIDELINES.md`, consultarlo para patrones correctos y ejemplos**

---

## 🧪 Flujo de trabajo estándar

1. Leer código, proponer plan y pedir aprobación.
2. **VERIFICAR THREAD SAFETY** antes de cualquier cambio en componentes visuales.
3. Hacer cambios específicos y controlados.
4. Yo compilo y testeo en DAW, luego doy feedback.
5. Documentar cambios y proponer commit adecuado.
6. **No proceder sin aprobación.**
7. **No eliminar código funcional sin consentimiento.**
8. **NO ASUMIR thread safety sin verificación exhaustiva.**

---

## 🔧 Technical Notes

- **Gen~ I/O**: 2 inputs (L/R), 2 outputs (L/R) + posibles outputs adicionales para medidores.
- **Latencia**: Añadir siempre +1 sample para compensar latencia mínima Gen~.
- **Thread-safe parameters**: Usar CustomSliderAttachment y UndoableButtonAttachment cuando estén disponibles.
- **Sample Rate**: El reverb debe adaptarse correctamente a diferentes sample rates.

---

## 🔨 Comandos útiles

### Configuración (OBLIGATORIO usar -G Ninja)
```bash
# Configuración estándar Debug/Release
cmake -B cmake-build-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release

# Con soporte AAX (requiere AAX SDK)
cmake -B cmake-build-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DJUCE_BUILD_AAX=ON
cmake -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release -DJUCE_BUILD_AAX=ON

# Desactivar auto-instalación de plugins
cmake -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release -DJUCE_AUTO_INSTALL_PLUGINS=OFF
```

### Compilación
```bash
cmake --build cmake-build-debug
cmake --build cmake-build-release
```

### Testing con pluginval (solo lo hace el usuario)
```bash
# Entrar al directorio de build apropiado
cd cmake-build-debug    # para Debug builds
cd cmake-build-release  # para Release builds

# Ejecutar tests de validación (puede tardar varios minutos)
ctest -C Debug -R pluginval -V      # para Debug
ctest -C Release -R pluginval -V    # para Release

# Ejecutar test específico de un formato
ctest -C Release -R JCBReverb_VST3 -V
ctest -C Release -R JCBReverb_AU -V
```

---

## 🎛️ Parámetros del Reverb - Exportados desde Gen~

### ✅ Lista completa de 23 parámetros del motor Gen~:

```cpp
// PARÁMETROS DEL REVERB
Param a_input;      // Input gain (ganancia de entrada)
Param b_drywet;     // Dry/Wet mix (mezcla señal seca/procesada)
Param c_reflect;    // Reflections (reflexiones tempranas)
Param d_damp;       // Damping (amortiguación de frecuencias altas)
Param e_size;       // Room size (tamaño de sala)
Param f_st;         // Stereo width (amplitud estéreo)
Param g_freeze;     // Freeze mode (congela el buffer del reverb)

// PARÁMETROS DEL EQ
Param h_lowGain;    // Low shelf gain (ganancia de graves)
Param i_peakGain;   // Peak gain (ganancia de medios)
Param j_hiGain;     // High shelf gain (ganancia de agudos)
Param n_lowFreq;    // Low shelf frequency (frecuencia de graves)
Param o_peakFreq;   // Peak frequency (frecuencia central)
Param p_hiFreq;     // High shelf frequency (frecuencia de agudos)
Param q_onoffEQ;    // EQ bypass (on/off del ecualizador)

// PARÁMETROS DE FILTRADO
Param k_lpf;        // Low pass filter cutoff (filtro pasa bajos)
Param l_hpf;        // High pass filter cutoff (filtro pasa altos)

// PARÁMETROS DEL COMPRESOR
Param r_onoffCOMP;  // Compressor bypass (on/off del compresor)
Param s_thd;        // Threshold (umbral de compresión)
Param t_ratio;      // Ratio (relación de compresión)
Param u_atk;        // Attack time (tiempo de ataque)
Param v_rel;        // Release time (tiempo de liberación)
Param w_makeup;     // Makeup gain (ganancia de compensación)

// PARÁMETRO DE SALIDA
Param m_output;     // Output gain (ganancia de salida)
```

### 🎨 Mapeo sugerido UI → Parámetros:

| Control UI | Parámetro | Rango típico | Formato | Descripción |
|------------|-----------|--------------|---------|-------------|
| inputSlider | a_input | -12 a +12 dB | "X.X dB" | Ganancia de entrada |
| drywetSlider | b_drywet | 0-100% | "X %" | Balance Dry/Wet |
| reflectSlider | c_reflect | 0-1 | "X.XX" | Intensidad reflexiones |
| dampSlider | d_damp | 0-1 | "X.XX" | Amortiguación HF |
| sizeSlider | e_size | 0-1 | "X.XX" | Tamaño de sala |
| stereoSlider | f_st | 0-1 | "X.XX" | Amplitud estéreo |
| freezeButton | g_freeze | 0/1 | Toggle | Freeze mode |
| eqBypassButton | q_onoffEQ | 0/1 | Toggle | EQ on/off |
| compBypassButton | r_onoffCOMP | 0/1 | Toggle | Comp on/off |
| outputSlider | m_output | -12 a +12 dB | "X.X dB" | Ganancia de salida |

---

## 🧩 Estructura del proyecto

```
JCBReverb/
├── Source/
│   ├── PluginProcessor.* (23 parámetros Gen~ + procesamiento)
│   ├── PluginEditor.* (GUI principal)
│   ├── Components/
│   │   ├── UI/
│   │   │   ├── CustomSlider.* (sistema de knobs personalizado)
│   │   │   ├── SpectrumAnalyzerComponent.* (analizador FFT si existe)
│   │   │   ├── GradientMeter.* (medidores RMS/pico)
│   │   │   └── CustomComboBox.* (selectores personalizados)
│   │   └── Windows/
│   │       ├── CodeWindow.* (visualizador de código Gen~)
│   │       └── CreditsWindow.* (ventana de créditos)
│   └── Helpers/
│       └── UndoableParameterHelper.* (undo/redo thread-safe)
├── exported-code/
│   ├── JCBReverb.cpp/h (código Gen~ exportado)
│   └── gen_dsp/ (librería Gen~)
├── Assets/
│   ├── FactoryPresets/ (presets de fábrica)
│   └── code/ (documentación de bloques Gen~)
└── CMakeLists.txt (configuración del proyecto)
```

---

## 📝 Notas importantes

- **No editar manualmente** el código Gen~ en `exported-code/` - se regenera desde Max/MSP.
- **Auto-instalación**: Los plugins se instalan automáticamente en `~/Library/Audio/Plug-Ins/` si `JUCE_AUTO_INSTALL_PLUGINS=ON`.
- **Recursos binarios**: PNG y presets incrustados con `juce_add_binary_data`.
- **Testing automático**: `pluginval` valida VST3 y AU (no AAX por limitaciones del framework).
- **AAX SDK**: Requerido solo para formato AAX, se busca en `$HOME/SDK/aax-sdk-2-8-1`.
- **Arquitecturas**: Universal binary (Intel + Apple Silicon) por defecto.
- **Thread safety**: Crítico para estabilidad en DAWs profesionales.

---

## 📋 Estado actual del proyecto

### ⚠️ **Estado inicial - Plugin en desarrollo**

#### **Tareas pendientes:**
- [ ] Implementar interfaz gráfica completa
- [ ] Conectar los 23 parámetros Gen~ con controles UI
- [ ] Implementar sistema de presets
- [ ] Añadir visualización de respuesta del reverb
- [ ] Implementar medidores de nivel
- [ ] Validar thread safety en todos los componentes
- [ ] Testing exhaustivo en DAWs
- [ ] Optimización de rendimiento

#### **Factory Presets disponibles:**
Los siguientes presets están en `Assets/FactoryPresets/`:
- Bass_Bass_Destroyer.preset
- Drums_Acoustic_Kick_Long.preset
- Drums_Kick_Bright.preset
- Drums_Snare_Broken_Bottom.preset
- Fx_808_Bd_Crush.preset
- Guitars_Guitar_Distortion.preset
- Guitars_Strat_Overdrive.preset
- (y otros...)

---

## 🚨 Recordatorios críticos

1. **NO modificar** archivos sin aprobación explícita
2. **NO eliminar** código que pueda ser útil más adelante  
3. **SIEMPRE** proponer cambios antes de implementar
4. **DOCUMENTAR** cada cambio realizado
5. **RESPETAR** el flujo de trabajo: proponer → aprobar → implementar → verificar
6. **VERIFICAR** thread safety en CADA componente visual

---

## 🔄 Estado para Nueva Sesión

### ✅ **Documentación inicial creada**

**Este documento está preparado** para guiar el desarrollo del plugin JCBReverb:

- ✅ **23 parámetros Gen~** documentados y listos para implementar
- ✅ **Estructura del proyecto** definida basada en estándares JCB
- ✅ **Thread safety guidelines** incluidas (CRÍTICO)
- ✅ **Comandos de compilación** configurados para CLion + Ninja
- ✅ **Factory presets** identificados y listos para usar

### 🚀 **Próximos pasos sugeridos (OBSOLETO - Ver sección del 30 de Agosto)**

1. ~~Revisar el código actual en `Source/` para entender el estado de implementación~~
2. ~~Verificar qué componentes UI ya están implementados~~
3. Mapear los 23 parámetros Gen~ a controles de interfaz
4. Implementar visualización específica del reverb
5. Añadir sistema de gestión de presets
6. Validar thread safety en todos los componentes

---

## 🔄 Estado para Nueva Sesión - 30 de Agosto 2025

### 📅 **Estado actual del proyecto**

#### 🔧 **Trabajo realizado en esta sesión:**

1. **Eliminación masiva de código de distorsión** - El plugin fue copiado de JCBDistortion y contenía 648+ referencias incorrectas
2. **Comentado sistemático de código problemático:**
   - ✅ Eliminados SpectrumAnalyzerComponent y DistortionCurveComponent (causaban crashes)
   - ✅ Comentados todos los structs de controles de distorsión en PluginEditor.h
   - ✅ Comentado método setupKnobs() completo (líneas 1524-2245)
   - ✅ Comentados métodos update de componentes inexistentes
   - ✅ Comentadas referencias en buttonClicked(), resized(), destructor
   - ✅ Comentados bloques de reset de sliders (líneas 2483-2531)
   - ✅ Comentadas secciones alrededor de líneas 3327-3355
   - ✅ Comentadas secciones en updateSliderValues() y getParameterIndexFromControl()

#### ⚠️ **QUEDAN 20 ERRORES DE COMPILACIÓN:**

**Últimas referencias por comentar (líneas 4112-4121 en updateAllTooltips()):**
```cpp
// Líneas que aún causan errores:
sidechainControls.scButton.setTooltip(...)
sidechainControls.xLowSlider.setTooltip(...)
sidechainControls.bandSlider.setTooltip(...)
sidechainControls.xHighSlider.setTooltip(...)
sidechainControls.bandSoloButton.setTooltip(...)
rightTopControls.safeLimitButton.setTooltip(...)
leftBottomKnobs.toneLpfButton.setTooltip(...)
leftBottomKnobs.toneFreqSlider.setTooltip(...)
leftBottomKnobs.toneQSlider.setTooltip(...)
leftBottomKnobs.tonePosButton.setTooltip(...)
```

#### 📋 **TODO para próxima sesión:**

1. **URGENTE: Comentar últimas referencias** en updateAllTooltips() (líneas 4112-4121)
2. **Verificar compilación** - debería compilar sin errores después de comentar las últimas líneas
3. **Implementar controles correctos de reverb:**
   - Controles input/output con escala ±12 dB (según indicó el usuario)
   - Los 23 parámetros Gen~ ya documentados en este archivo

#### 💡 **Notas importantes del usuario:**

- Los controles de input/output eventualmente tendrán rangos ±12 dB
- Actualmente pueden estar en escala lineal mientras se modifica el patch Gen~
- El objetivo es sincronizar los rangos entre Gen~ y la interfaz
- **CRÍTICO**: El usuario enfatizó la importancia de estudiar bien el código y no dar soluciones apresuradas
- El plugin crasheaba en REAPER al intentar cargar debido a las referencias incorrectas de distorsión

#### 📊 **Métricas del problema:**

- **648+ referencias** a controles de distorsión que no existen en reverb
- **20 errores finales** por resolver en tooltips (líneas 4112-4121)
- **Archivos eliminados**: SpectrumAnalyzerComponent y DistortionCurveComponent
- **Método más grande comentado**: setupKnobs() con 721 líneas

#### 🎯 **Estrategia de solución adoptada:**

1. **Fase 1**: Eliminar archivos que causan crashes inmediatos
2. **Fase 2**: Comentar sistemáticamente todas las referencias a controles inexistentes
3. **Fase 3**: Crear plugin mínimo compilable
4. **Fase 4**: Implementar interfaz correcta de reverb desde cero

---

*Última actualización: 30 de Agosto 2025 - Sesión de limpieza masiva de código de distorsión*