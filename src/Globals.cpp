#include "tp_image_utils_emcc/Globals.h"

#include "tp_image_utils_emcc/LoadImages.h"

#include "tp_image_utils/LoadImages.h"

//##################################################################################################
//! A module of image loading functions that work in Emscripten.
namespace tp_image_utils_emcc
{

//##################################################################################################
void init()
{
  tp_image_utils::loadImageFromData_ = loadImageFromData;
}

}
