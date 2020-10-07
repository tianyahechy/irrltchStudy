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
#elif defined( __GNUC__)
#define PACK_STRUCT __attribute__ ((packed))
#else
#error compiler not supported
#endif // _MSC_VER
	
		struct SBMPHeader
		{
			u16 Id;
			u32 fileSie;
			u32 reserved;
			u32 bitmapDataOffset;
			u32 bitmapHeaderSize;
			u32 width;
			u32 height;
			u16 planes;
			u16 bpp;
			u32 compression;
			u32 bitmapDataSize;
			u32 pixelPerMeterX;
			u32 pixelPerMmeterY;
			u32 colors;
			u32 importantColors;
		} PACK_STRUCT;
#ifdef _MSC_VER
#pragma pack (pop, packing)
#endif
#undef PACK_STRUCT

		class CSurfaceLoaderBmp : public ISurfaceLoader
		{
		private:
			c8 * _bmpData;
			s32 * _paletteData;
			void decompres8BitRLE(c8 * bmpData, s32 size, s32 width, s32 height, s32 pitch);
			void decompress4BitRLE(c8* & bmpData, s32 size, s32 width, s32 height, s32 pitch);

		public:
			CSurfaceLoaderBmp();
			virtual ~CSurfaceLoaderBmp();

			virtual bool isALoadableFileExtension(const c8* fileName);
			virtual bool isALoadableFileFormat(irr::io::IReadFile* file);
			virtual ISurface * loadImage(irr::io::IReadFile* file);

		};
	}
}