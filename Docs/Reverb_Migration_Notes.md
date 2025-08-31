# JCBReverb – Notas de migración y lecciones aprendidas

Breve resumen de los problemas encontrados en la migración desde JCBDistortion y cómo evitarlos desde el inicio en próximos plugins.

## 1) Crash al instanciar (host)
- Causa: accesos fuera de rango a salidas de Gen. El export de reverb entregaba 2 outs (out1/out2), pero el host heredado intentaba leer out3/out4/out5/out6 (post‑TRIM, GR, etc.). Esto provocó UB y crash inmediato.
- Solución: dos enfoques válidos (usar ambos ayuda):
  - Gen: declarar explícitamente las salidas adicionales necesarias (p. ej., out4/out5 = post‑TRIM L/R) y mantener la convención en todos los plugins.
  - Host: antes de leer salidas extra, comprobar `num_outputs()`. Si no existen, usar fallback (entrada capturada) y evitar lecturas fuera de rango.
- Recomendación: acordar desde el principio el mapa de salidas de Gen (1/2 = main, 4/5 = post‑TRIM, 3 = reservado/0) y reflejarlo en el host con guards.

## 2) FREEZE (estabilidad)
- Semántica correcta para evitar explosiones:
  - Cortar la entrada a la reverb al activar FREEZE: `preInput* = in* * (1 - freezeOn)` (sin smoothing).
  - Forzar `SIZE` a 0.999 (y no exceder) mientras FREEZE está activo, y usar ese valor en combs y allpass.
  - Mantener `REFLECT`/`DAMP` estables (no gatear ni atenuar temporalmente durante FREEZE).
  - Asegurar que offsets de delay están clippeados a `[0, samplerate-1]`.
- Error que lo rompió durante pruebas: invertir/alterar el mapeo de `DAMP` y/o aplicar envolventes externas (duck/gate) al tanque durante FREEZE. Evitarlo.

## 3) Bump al cambiar PRE/POST (EQ/COMP)
- Causa: cambiar la ubicación (PRE→POST) modifica la excitación del tanque (espectro/nivel), y al ser un sistema con feedback, aparece un pico perceptible.
- Estrategias testadas:
  - Crossfades/normalización de energía: mitigaron pero no eliminaron del todo.
  - Enfoque efectivo y ligero: “gap corto” (~8–12 ms) en el feed del tanque al detectar el cambio, con PRE y POST siempre corriendo. No tocar la salida ni FREEZE. Resultado estable sin bump sostenido.
  - Alternativa (CPU↑): doble línea de reverb en paralelo y crossfade de salidas.
- Recomendación: implementar el gap en Gen (conmutador binario + env corto) y mantener el host ajeno a esa lógica.

## 4) Mapeo de parámetros (APVTS ↔ Gen)
- Alinear IDs y rangos desde el inicio:
  - Usar exactamente los nombres exportados por Gen (con mayúsculas): `a_INPUT … w_MAKEUP`, `x_PREPOST`, `y_IOMODE`, `z_SOFTCLIP`.
  - Mantener el mismo orden/índices que el export (0..N‑1) en `parameterChanged`.
  - Evitar IDs “legacy” en minúsculas heredados de otros proyectos.
- Bypass del host: usar el parámetro estándar `"bypass"` del APVTS (no un id custom tipo `f_BYPASS`). Los attachments deben apuntar a parámetros válidos.

## 5) UI heredada (Editor)
- Problema: referencias a controles de Distortion (tilt, bits, sidechain, etc.) que no existen en la reverb → errores de compilación o crashes.
- Solución:
  - Neutralizar/encapsular referencias a esos controles hasta que la UI de reverb esté lista.
  - Reutilizar la plantilla de Editor sólo con los componentes necesarios; el resto, tras `#if 0` o comentado claramente.
- Recomendación: preparar una plantilla de UI básica con menús/botones genéricos y bloques opcionales deshabilitables por `#define` o CMake options.

## 6) Convenciones recomendadas
- Salidas Gen: 1/2 = main L/R, 4/5 = post‑TRIM L/R (3 = 0 o reservado). El host comprueba `num_outputs()`.
- FREEZE: entrada a 0 y `SIZE≤0.999`, sin tocar reflect/damp; no gates/ducks ajenos.
- PRE/POST: procesadores siempre activos; conmutador afecta sólo ganancias, con gap corto en feed.
- DAMP: `pass = 1 − d_DAMP`, `leak = d_DAMP` (0 = sin amortiguamiento, 1 = filtrado máximo).

## Checklist para el siguiente plugin
- [ ] Exportar Gen con mapa de salidas acordado y nombres de parámetros definitivos.
- [ ] Añadir guards en el host para `num_outputs()` antes de leer outs extra.
- [ ] Verificar FREEZE (input=0, size clamp, delays clip) con `e_SIZE` extremos.
- [ ] Implementar PRE/POST como gap corto en Gen; sin alterar salida ni FREEZE.
- [ ] APVTS: crear parámetros con IDs/nombres exactos de Gen; attachments al parámetro correcto (p. ej., `bypass`).
- [ ] Editor: activar sólo bloques de UI necesarios; deshabilitar/ocultar lo heredado hasta que se use.
