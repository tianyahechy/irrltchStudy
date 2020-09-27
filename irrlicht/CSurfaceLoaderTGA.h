#pragma once
#include "ISurfaceLoader.h"
namespace irr
{
	namespace video
	{
#ifdef _MSC_VER
#pragma pack(push, packing)
#pragma pack(1)
#define PACK_STRUCT
#elif defined(__GNUC__)
#define PACK_STRUCT __attribute__ (( packed))
#else
#error compiler not supported
#endif

		struct STGAHeader
		{
			u8 IdLength;
			u8 ColorMapType;
			u8 ImageType;
			u8 FirstEntryIndex[2];
			u16 ColorMapLength;
			u8	ColorMapEntrySize;
			u8	XOrigin[2];
			u8	YOrigin[2];
			u16 ImageWidth;
			u16	ImageHeight;
			u8	PixelDepth;
			u8	ImageDescriptor;
		}PACK_STRUCT;

#ifdef _MSC_VER
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

		class CSurfaceLoaderTGA : public ISurfaceLoader
		{
		public:

			//! constructor
			CSurfaceLoaderTGA();

			//! destructor
			virtual ~CSurfaceLoaderTGA();

			//! returns true if the file maybe is able to be loaded by this class
			//! based on the file extension (e.g. ".tga")
			virtual bool isALoadableFileExtension(const c8* fileName);

			//! returns true if the file maybe is able to be loaded by this class
			virtual bool isALoadableFileFormat(irr::io::IReadFile* file);

			//! creates a surface from the file
			virtual ISurface* loadImage(irr::io::IReadFile* file);


		};
	}

}