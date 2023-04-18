#include "tp_image_utils_emcc/LoadImages.h"
#include "tp_image_utils_emcc/ReadJPEG.h"
#include "tp_image_utils_emcc/ReadPNG.h"
#include "tp_image_utils_emcc/ReadWebP.h"

namespace tp_image_utils_emcc
{

//##################################################################################################
tp_image_utils::ColorMap TP_IMAGE_UTILS_EMCC_EXPORT loadImageFromData(const std::string& data)
{
#ifndef NO_WEBP
  if(tpStartsWith(data, "RIFF"))
    return readWebP(data);
#endif

#ifndef NO_JPEG
  if(tpStartsWith(data, "\xFF\xD8"))
    return readJPEG(data);
#endif

#ifndef NO_PNG
  if(tpStartsWith(data, "\x89PNG"))
    return readPNG(data);
#endif

  return tp_image_utils::ColorMap();
}

}
