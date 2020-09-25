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

		struct PsdHeader
		{
			c8 signature[4];
			u16 version;
			c8 reserved[6];
			u16 channels;
			u32 height;
			u32 width;
			u16 depth;
			u16 mode;
		}PACK_STRUCT;

#ifdef _MSC_VER
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

		class CSurfaceLoaderPSD : public ISurfaceLoader
		{
		public:

			//! constructor
			CSurfaceLoaderPSD();

			//! destructor
			virtual ~CSurfaceLoaderPSD();

			//! returns true if the file maybe is able to be loaded by this class
			//! based on the file extension (e.g. ".tga")
			virtual bool isALoadableFileExtension(const c8* fileName);

			//! returns true if the file maybe is able to be loaded by this class
			virtual bool isALoadableFileFormat(irr::io::IReadFile* file);

			//! creates a surface from the file
			virtual ISurface* loadImage(irr::io::IReadFile* file);

		private:
			PsdHeader _header;
			u32* _imageData;
			bool _error;

			bool readRawImageData(irr::io::IReadFile* file);
			bool readRLEImageData(irr::io::IReadFile* file);
			c8 getShiftFromChannel(c8 channelNr);

			inline u32 convert21e(u32 value)
			{
				value = (value >> 16) | (value << 16);
				value = ((value >> 8) & 0xFF00FF) | ((value << 8) & 0xFF00FF00);
				return value;
			}

			inline u16 convert21e(u16 value)
			{
				value = (value >> 8) | (value << 8);
				return value;
			}

		};
	}

}