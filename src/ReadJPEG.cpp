#include "tp_image_utils_emcc/ReadJPEG.h"

#ifndef NO_JPEG

#include <jpeglib.h>
#include <setjmp.h>

#include <cstring>

namespace tp_image_utils_emcc
{

namespace
{

//##################################################################################################
struct my_error_mgr
{
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

//##################################################################################################
/*
 * Here's the routine that will replace the standard error_exit method:
 */
void my_error_exit(j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = reinterpret_cast<my_error_ptr>(cinfo->err);

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}
}

//##################################################################################################
tp_image_utils::ColorMap readJPEG(const std::string& data)
{
   struct jpeg_decompress_struct cinfo;
   struct my_error_mgr jerr;

   JSAMPARRAY buffer;
   int row_stride;

   cinfo.err = jpeg_std_error(&jerr.pub);
   jerr.pub.error_exit = my_error_exit;
   if(setjmp(jerr.setjmp_buffer))
   {
     jpeg_destroy_decompress(&cinfo);
     return 0;
   }

   jpeg_create_decompress(&cinfo);

   jpeg_mem_src(&cinfo,
                reinterpret_cast<const unsigned char*>(data.data()),
                static_cast<unsigned long>(data.size()));

   jpeg_read_header(&cinfo, TRUE);
   jpeg_start_decompress(&cinfo);


   row_stride = cinfo.output_width * cinfo.output_components;
   buffer = (*cinfo.mem->alloc_sarray)(reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, row_stride, 1);

   size_t width = cinfo.output_width;
   size_t height = cinfo.output_height;

   tp_image_utils::ColorMap pixels{width, height};
   TPPixel* pixelData = pixels.data();

   while(cinfo.output_scanline < cinfo.output_height)
   {
     jpeg_read_scanlines(&cinfo, buffer, 1);
     for(size_t i=0; i<width; i++, pixelData++)
     {
       auto* src = &buffer[0][i*3];
       pixelData->r = src[0];
       pixelData->g = src[1];
       pixelData->b = src[2];
       pixelData->a = 255;
     }
   }

   jpeg_finish_decompress(&cinfo);
   jpeg_destroy_decompress(&cinfo);

  return pixels;
}

}

#endif
