#ifndef tp_image_utils_emcc_Globals_h
#define tp_image_utils_emcc_Globals_h

#include "lib_platform/Globals.h"

#if defined(TP_IMAGE_UTILS_EMCC_LIBRARY)
#  define TP_IMAGE_UTILS_EMCC_EXPORT TP_EXPORT
#else
#  define TP_IMAGE_UTILS_EMCC_EXPORT TP_IMPORT
#endif

//##################################################################################################
//! A module of image loading functions that work in Emscripten.
namespace tp_image_utils_emcc
{

//##################################################################################################
void init();

}

#endif
