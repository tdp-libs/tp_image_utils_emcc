#include "tp_image_utils_emcc/ReadPNG.h"

#ifndef NO_PNG

#include "tp_utils/DebugUtils.h"

#include <png.h>

#include <cstring>

namespace tp_image_utils_emcc
{

namespace
{
//################################################################################################
struct Data_lt
{
  const char* data;
  size_t index{0};
  size_t max;
};

//################################################################################################
static void readBytes(png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead)
{
  Data_lt* data = reinterpret_cast<Data_lt*>(png_get_io_ptr(png_ptr));
  if(data == nullptr)
    return;

  if((data->index+byteCountToRead)>data->max)
    return;

  std::memcpy(outBytes, data->data+data->index, byteCountToRead);
  data->index+=byteCountToRead;
}
}

//##################################################################################################
tp_image_utils::ColorMap readPNG(const std::string& data)
{
  Data_lt dataStream;
  dataStream.data = data.c_str();
  dataStream.max = data.size();

  auto fail = [&](const std::string& message)
  {
    tpWarning() << "Load PNG error: " << message;
    return tp_image_utils::ColorMap();
  };

  if(png_sig_cmp(reinterpret_cast<png_const_bytep>(data.c_str()), 0, 8))
    return fail("Issue with header.");


  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png_ptr)
    return fail("Failed to create png_create_read_struct.");

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr)
    return fail("Failed to create png_create_info_struct.");

  //if(setjmp(png_jmpbuf(png_ptr)))
  //  return fail("Error during init_io.");

  png_set_read_fn(png_ptr,& dataStream, readBytes);
  png_set_sig_bytes(png_ptr, 0);

  png_read_info(png_ptr, info_ptr);

  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  int number_of_passes = png_set_interlace_handling(png_ptr);
  TP_UNUSED(number_of_passes);
  png_read_update_info(png_ptr, info_ptr);

  if(bit_depth!=8)
    return fail("Only 8 bit images supported.");

  //if(setjmp(png_jmpbuf(png_ptr)))
  //  return fail("Error during read_image.");

  png_bytep* row_pointers = static_cast<png_bytep*>(malloc(sizeof(png_bytep) * height));
  TP_CLEANUP([&]{free(row_pointers);});

  for(int y=0; y<height; y++)
    row_pointers[y] = static_cast<png_byte*>(malloc(png_get_rowbytes(png_ptr,info_ptr)));

  png_read_image(png_ptr, row_pointers);

  tp_image_utils::ColorMap pixels{size_t(width), size_t(height)};
  auto p = pixels.data();
  switch(color_type)
  {
  case PNG_COLOR_TYPE_RGB_ALPHA:
  {
    for(int y=0; y<height; y++)
    {
      auto row = row_pointers[y];
      for(int x=0; x<width; x++)
      {
        p->r = row[0];
        p->g = row[1];
        p->b = row[2];
        p->a = row[3];
        row+=4;
        p++;
      }
    }
    break;
  }
  case PNG_COLOR_TYPE_RGB:
  {
    for(int y=0; y<height; y++)
    {
      auto row = row_pointers[y];
      for(int x=0; x<width; x++)
      {
        p->r = row[0];
        p->g = row[1];
        p->b = row[2];
        p->a = 255;
        row+=3;
        p++;
      }
    }
    break;
  }

  default:
  tpWarning() << "Color type: " << int(color_type);
  return fail("Color type not supported.");
  }

  return pixels;
}

}

#endif
