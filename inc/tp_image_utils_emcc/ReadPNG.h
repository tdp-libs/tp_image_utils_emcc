#ifndef tp_image_utils_emcc_ReadPNG_h
#define tp_image_utils_emcc_ReadPNG_h

#ifndef NO_PNG

#include "tp_image_utils_emcc/Globals.h"

#include "tp_image_utils/ColorMap.h"

namespace tp_image_utils_emcc
{

//##################################################################################################
tp_image_utils::ColorMap TP_IMAGE_UTILS_EMCC_EXPORT readPNG(const std::string& data);

}

#endif

#endif
