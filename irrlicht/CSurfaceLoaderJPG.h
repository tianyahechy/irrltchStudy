#pragma once

#include "ISurfaceLoader.h"
#include <stdio.h>

extern "C"
{
#include "jconfig.h"
#include "jpeglib.h"
}

namespace irr
{
	namespace video
	{

		class CSurfaceLoaderJPG : public ISurfaceLoader
		{
		public:

			//! constructor
			CSurfaceLoaderJPG();

			//! destructor
			virtual ~CSurfaceLoaderJPG();

			//! returns true if the file maybe is able to be loaded by this class
			//! based on the file extension (e.g. ".tga")
			virtual bool isALoadableFileExtension(const c8* fileName);

			//! returns true if the file maybe is able to be loaded by this class
			virtual bool isALoadableFileFormat(irr::io::IReadFile* file);

			//! creates a surface from the file
			virtual ISurface* loadImage(irr::io::IReadFile* file);

		private:
			static void init_source(j_decompress_ptr cinfo);
			static u8 fill_input_buffer(j_decompress_ptr cinfo);
			static void skip_input_data(j_decompress_ptr cinfo, long num_bytes);
			static void resync_to_restart(j_decompress_ptr cinfo, long desired);
			static void term_source(j_decompress_ptr cinfo);

		};

	}
}