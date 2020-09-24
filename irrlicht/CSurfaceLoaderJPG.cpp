#include "CSurfaceLoaderJPG.h"
#include <string.h>
#include "CColorConverter.h"

namespace irr
{
	namespace video
	{
		CSurfaceLoaderJPG::CSurfaceLoaderJPG()
		{
		}
		CSurfaceLoaderJPG::~CSurfaceLoaderJPG()
		{
		}
		bool CSurfaceLoaderJPG::isALoadableFileExtension(const c8* fileName)
		{
			return strstr(fileName, ".jpg") != 0;
		}
		bool CSurfaceLoaderJPG::isALoadableFileFormat(irr::io::IReadFile* file)
		{
			if (!file)
			{
				return false;
			}
			s32 jfif = 0;
			file->seek(6);
			file->read(&jfif, sizeof(s32));
			return (jfif == 'JFIF' || jfif == 'FIFJ');
		}
		ISurface* CSurfaceLoaderJPG::loadImage(irr::io::IReadFile* file)
		{
			file->seek(0);
			file->getSize();
			u8* input = new u8[file->getSize()];
			file->read((input, file->getSize());
			struct jpeg_decompress_struct cinfo;
			struct jpeg_error_mgr jerr;

			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_decompress(&cinfo);
			jpeg_source_mgr jsrc;
			jsrc.bytes_in_buffer = file->getSize();
			jsrc.next_input_byte = (JOCTET*)input;
			cinfo.src = &jsrc;

			jsrc.init_source = init_source;
			jsrc.fill_input_buffer = fill_input_buffer;
			jsrc.skip_input_data = skip_input_data;
			jsrc.resync_to_restart = jpeg_resync_to_restart;
			jsrc.term_source = term_source;

			jpeg_read_header(&cinfo, TRUE);
			
			u16 rowSpan = cinfo.image_width * cinfo.num_components;
			unsigned width = cinfo.image_width;
			unsigned height = cinfo.image_height;

			bool has_alpha = false;
			bool greyScale;

			if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
			{
				greyScale = true;
			}
			else
			{
				greyScale = false;
			}
			u8* output = new u8[rowSpan * height];
			u8** rowPtr = new u8 * [height];
			for (unsigned i = 0; i < height; i++)
			{
				rowPtr[i] = &output[i * rowSpan];
			}
			unsigned rowsRead = 0;
			while (cinfo.output_scanline < cinfo.output_height)
			{
				rowsRead += jpeg_read_scanlines(&cinfo, &rowPtr[rowsRead], cinfo.output_height - rowsRead);
			}
			delete[] rowPtr;

			jpeg_destroy_decompress(&cinfo);
			video::ISurface* surface = video::createSurface(core::dimension2d<s32>(width, height));
			CColorConverter::convert32BitTo16BitFlipColorShuffle((c8*)((void*)output), surface->lock(), width, height, 0);

			delete[] input;
			delete[] output;

			return surface;

		}
		void CSurfaceLoaderJPG::init_source(j_decompress_ptr cinfo)
		{
		}
		u8 CSurfaceLoaderJPG::fill_input_buffer(j_decompress_ptr cinfo)
		{
			return 1;
		}
		void CSurfaceLoaderJPG::skip_input_data(j_decompress_ptr cinfo, long num_bytes)
		{
			jpeg_source_mgr* src = cinfo->src;
			if (num_bytes > 0)
			{
				src->bytes_in_buffer -= num_bytes;
				src->next_input_byte += num_bytes;
			}
		}
		void CSurfaceLoaderJPG::resync_to_restart(j_decompress_ptr cinfo, long desired)
		{
		}
		void CSurfaceLoaderJPG::term_source(j_decompress_ptr cinfo)
		{
		}

		ISurfaceLoader* createSurfaceLoaderJPG()
		{
			return new CSurfaceLoaderJPG;
		}
	}
}