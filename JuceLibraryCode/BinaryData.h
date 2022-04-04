/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   verde_jpg;
    const int            verde_jpgSize = 17573;

    extern const char*   morado_jpg;
    const int            morado_jpgSize = 16379;

    extern const char*   azul_jpg;
    const int            azul_jpgSize = 13061;

    extern const char*   fondo_700_200_png;
    const int            fondo_700_200_pngSize = 7897;

    extern const char*   fondo_1400_400_png;
    const int            fondo_1400_400_pngSize = 13546;

    extern const char*   fondo_2800_800_png;
    const int            fondo_2800_800_pngSize = 33683;

    extern const char*   background_700_200_jpg;
    const int            background_700_200_jpgSize = 21025;

    extern const char*   solo_fondo_700_227_png;
    const int            solo_fondo_700_227_pngSize = 8095;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
