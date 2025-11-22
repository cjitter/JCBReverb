# Changelog

Todas las versiones de este proyecto siguen [Semantic Versioning](https://semver.org/).

## [1.0.1] - 2025-11-21
### Added
- Infraestructura de sincronización APVTS ↔ Gen (caché de parámetros y helpers internos).

### Changed
- Restauración de estado: reemplazado recorrido manual por `enqueueAllParametersForAudioThread()`.
- Carga de presets: sincronización con Gen vía cola segura (`pushGenParamByName`), sin escribir directo en Gen.

### Removed
- Eliminados clamps y referencias a parámetros ajenos al plugin (`b_DRIVE`, `d_MODE`, `d_ATK`, `e_REL`).

## [1.0.0] - 2025-11-21
### Initial Release
- Versión inicial del plugin.