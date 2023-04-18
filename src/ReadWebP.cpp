#include "tp_image_utils_emcc/ReadWebP.h"

#ifndef NO_WEBP

#include "webp/decode.h"

#include <cstring>

namespace tp_image_utils_emcc
{
//##################################################################################################
tp_image_utils::ColorMap readWebP(const std::string& data)
{
  int width = 0;
  int height = 0;

  uint8_t* buffer = WebPDecodeRGB(reinterpret_cast<const uint8_t* >(data.c_str()),
                                  data.size(),
                                  &width,
                                  &height);

  if(!buffer)
    return tp_image_utils::ColorMap();

  tp_image_utils::ColorMap pixels{size_t(width), size_t(height)};

  auto src = buffer;
  TPPixel* dst = pixels.data();
  TPPixel* dstMax = dst+pixels.size();
  for(; dst<dstMax; src+=3, dst++)
  {
    dst->r = src[0];
    dst->g = src[1];
    dst->b = src[2];
    dst->a = 255;
  }

  WebPFree(buffer);

  return pixels;
}

}

#endif
