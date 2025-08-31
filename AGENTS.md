# Repository Guidelines

## Project Structure & Module Organization
- Source: `Source/PluginProcessor.*`, `Source/PluginEditor.*`
- DSP (gen~): `exported-code/JC_GENPLUGIN.*`, `exported-code/gen_dsp/*`
- Assets: `Assets/` (fondos, diagramas, presets en `Assets/FactoryPresets/`, textos UI en `Assets/code/`)
- Projucer/Xcode: `Builds/MacOSX/` (solo si se usa Projucer)
- Project file: `JCBReverb.jucer` (o `JCBReverbST.jucer` mientras dure la transición)

## Workflow & Tools
- Entorno principal: CLion + CMake con generador Ninja.
- No usar `cmake` sin `-G Ninja` fuera de CLion (salvo pruebas aisladas).
- Respeta los directorios de CLion: `cmake-build-debug`, `cmake-build-release`.
- Para Xcode/Projucer, usa un dir separado (p. ej., `build-xcode`) para no contaminar.
- No modificar scripts manuales: `build-xcode-*.sh` (se ejecutan solo por el usuario).

## Build & Test Commands
- Configuración (Ninja):
  - `cmake -B cmake-build-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug`
  - `cmake -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release`
  - Opciones: `-DJUCE_BUILD_AAX=ON` `-DJUCE_AUTO_INSTALL_PLUGINS=ON`
- Compilación: `cmake --build cmake-build-debug` (o `cmake-build-release`).
- Pluginval (si `cmake/Pluginval.cmake` existe): `ctest -C Debug -R pluginval -V` dentro del build dir.
- Limpieza VST3 (usuario): `rm -rf ~/Library/Audio/Plug-Ins/VST3/JCBReverb.vst3`.

## Thread Safety Rules (OBLIGATORIO)
- Nunca llamar GUI (`repaint`, `setVisible`, `setBounds`) desde `parameterChanged` o audio thread.
- Usar `MessageManager::callAsync` con `SafePointer` para actualizar UI.
- Compartidos cross-thread: `std::atomic<>` y evitar locks en `processBlock`.
- Auditar cada listener de parámetros antes de tocar la UI.

## Coding Style & Naming
- C++20, 4 espacios, estilo JUCE.
- Clases: PascalCase; miembros/métodos: camelCase.
- APVTS: IDs ordenados (`a_input`, `b_drywet`, …); mantener mapping por índice.

## Commit & PR Guidelines
- Flujo: proponer plan → pedir aprobación → implementar → yo valido en DAW.
- Commits en imperativo y acotados; PRs con descripción, pasos de prueba y capturas si cambia la UI.
- Al clonar como plantilla: actualizar `PRODUCT_NAME`, `BUNDLE_ID`, `PLUGIN_CODE` en `CMakeLists.txt` y `.jucer`.

## Security & Config
- AAX opcional: `-DJUCE_BUILD_AAX=ON` y `-DJUCE_AAX_SDK_PATH=$HOME/SDK/aax-sdk-2-8-1`.
- Auto‑instalación: `-DJUCE_AUTO_INSTALL_PLUGINS=ON/OFF`.

---

## Work Log (GenExpr – Reverb) – 2025-08-30

Resumen del estado actual (Codebox compila y suena):
- Archivo funcional y pegable: `Assets/code/GenExpr_readable.txt`.
- Parámetros renombrados a convención `letra_MAYUS`: `a_INPUT`, `m_OUTPUT`, `x_PREPOST` (PRE/POST EQ+COMP), `y_IOMODE` (I/O mono/mono, mono/stereo, stereo/stereo).
- Trims en dB (±12 dB) para entrada/salida; smoothing en lineal. El trim de salida afecta solo a la rama WET.
- Ruteo I/O explícito en Gen: `ioL/ioR` según `y_IOMODE`; colapso mono en salida si procede.
- PRE/POST EQ+COMP: PRE procesa antes de la reverb y desactiva el POST; POST como original si `x_PREPOST==0`.
- Encabezados/secciones estilo distorsionador; muchos aliases camelCase añadidos (smoothing, pre‑filtros, M/S, EQ/COMP, Dry/Wet, difusión).
- Compresor post reescrito con nombres legibles (RMS, env, makeup) y writes corregidos.

Trabajo de limpieza iniciado (parcial):
- Pre‑filtros: entradas/salidas legibles (`preFilterIn*`, `lpfOut*`, `hpfOut*`), salidas de sección actualizadas.
- M/S: comentarios detallados y uso de `msLeft/msRight` aguas abajo.
- EQ/COMP POST: eliminado `mix_799/mix_801`, ahora `postEqLeft/Right` y `wetPostCompLeft/Right`.
- Difusión: bancos comb y allpass con aliases por tap y por etapa; sumas normalizadas reescritas con nombres.

Pendiente para próxima sesión (orden sugerido):
1) Sustitución completa de `add_/mul_/gen_` restantes en bancos comb/allpass por nombres camelCase (ya definidos como aliases).
2) Unificación final de nombres en M/S (reemplazar usos residuales de internos por `ms*` legibles).
3) Revisión final de declares vs. expressions (Codebox) tras sustituciones masivas.
4) Documentación breve en cabecera del Codebox: bloques, parámetros y ruteo I/O.
5) Validación en Gen y luego en JUCE (mapear `y_IOMODE` desde BusesLayout; verificar que `a_INPUT/m_OUTPUT` en dB funcionan como trim y que PRE/POST se comporta bien).

Notas/riesgos:
- Cambios de nombres se hacen por bloques para no alterar comportamiento; hay muchos taps/estados, por lo que el refactor se hará en iteraciones cortas y verificables.
- El host (JUCE) debe fijar `y_IOMODE` explícitamente según `BusesLayout` para evitar heurísticas.

## Work Log (JUCE + Gen) – 2025-08-31

Resumen cambios relevantes (estado actual compila, instancia; queda bug de silencio tras parar):

- Gen (Codebox: `Assets/code/GenExpr_readable.txt`)
  - Limpieza mayor de nombres/aliases y bloques; biquads con coeficientes nombrados.
  - FREEZE estable: corta entrada (`preInput* = in* * (1 - freezeOn)`), fuerza `e_SIZE` a 0.999 (clip), offsets clip `[0, samplerate-1]`. No se gatea reflect/damp durante FREEZE.
  - PRE/POST: implementado enfoque “gap corto” en feed al conmutar `x_PREPOST` (procesadores PRE/POST siempre activos). Eliminadas pruebas de normalización/duck.
  - DAMP correcto: `pass = 1 - d_DAMP`, `leak = d_DAMP` (0 = sin amortiguamiento).
  - Softclip opcional `z_SOFTCLIP` (solo WET) con smoothing.
  - Añadidas salidas post‑TRIM en out4/out5 (L/R) para medidores del host.
  - Nuevo bypass interno con smoothing: `z_BYPASSS` (0=process, 1=DRY). Mezcla aplicada tras Dry/Wet y softclip, antes de DC‑block.

- Export Gen (`exported-code/JCBReverb.*`)
  - Verificado que el export actual publica 26 parámetros (incluye `x_PREPOST`, `y_IOMODE`, `z_SOFTCLIP`). Tras añadir `z_BYPASSS` en Codebox, re‑exportar para exponerlo (hecho por el usuario).

- Host JUCE
  - Crash al instanciar resuelto: el host leía outs inexistentes (3..6). Ahora usa out4/out5 si `num_outputs()>4`, y si no existen, fallback a entrada capturada.
  - APVTS alineado con IDs de Gen (mayúsculas) y rangos/defectos corregidos (incluye `x_PREPOST`, `y_IOMODE`, `z_SOFTCLIP`).
  - Botón BYPASS (UI) ahora controla el bypass interno `z_BYPASSS` directamente (no APVTS, no automatizable). Estado leído/escrito vía `JCBReverb::get/setparameter`.
  - `setStateInformation` crash (AU) arreglado: ID correcto `"bypass"` y null‑check; tras cargar estado, se re‑sincronizan todos los parámetros a Gen.
  - `prepareToPlay`: añadido `JCBReverb::reset(state)` y re‑sync de todos los parámetros a Gen.
  - Constructor: eliminada validación legacy de Distortion; ahora sync por nombres reales exportados.
  - Editor: neutralizadas referencias de UI heredada que impedían compilar o producían crashes (sin tocar estructura ni audio).

Problema pendiente (prioridad):
- En algunos casos, al parar el DAW de manera aleatoria, el audio deja de sonar (no cuelga). FREEZE y bypass interno parecen correctos; sospecha de desincronización/lifecycle entre Gen y host tras `stop`.

Hipótesis y próximos pasos (investigación):
- Revisar FSM de bypass suave del host (`processBlockCommon`) y transiciones `FadingToBypass/FadingToActive` frente a `hostWantsBypass()` y a bloque vacío; comprobar que no nos quedamos en estado Bypassed con mix secos/zap de buffers.
- Trazas (DBG) o contadores para: entrada WET/DRY, estado de `bypassState`, valores de `x_PREPOST`, `z_BYPASSS`, FREEZE, y confirmación de `JCBReverb::perform` llamado con `numSamples>0` tras reanudar.
- Confirmar que tras `reset()` no queda `z_BYPASSS` activo por defecto (debe ser 0) y que el editor no reescribe el bypass interno a 1 en `updateButtonValues()`.
- Verificar que en `releaseResources()` no vaciamos buffers necesarios y que `prepareToPlay` vuelve a llamar a `reset` en todas las rutas de reanudación del host.
- Probar a forzar un “wake-up” mínimo (p.ej., `JCBReverb::reset` condicional cuando `numSamples==0` varias veces consecutivas) si el host no envía audio continuo al reanudar.

Cómo reproducir (actual):
- REAPER macOS 15.6.1: insertar plugin, reproducir/parar repetidamente. En ocasiones el audio no vuelve tras `stop`. FREEZE no afectado.

Notas/tareas menores:
- Mantener out4/out5 como post‑TRIM L/R en Gen para consistencia y medidores.
- Dejar el bypass interno como control UI no automatizable (sin APVTS).
