#include <string.h>
#include "os.h"
#include "CColorConverter.h"
#include "CSurfaceLoaderTGA.h"

namespace irr
{
	namespace video
	{
		CSurfaceLoaderTGA::CSurfaceLoaderTGA()
		{
		}
		CSurfaceLoaderTGA::~CSurfaceLoaderTGA()
		{
		}

		bool CSurfaceLoaderTGA::isALoadableFileExtension(const c8* fileName)
		{
			return strstr(fileName, ".tga") != 0;
		}

		bool CSurfaceLoaderTGA::isALoadableFileFormat(irr::io::IReadFile* file)
		{
			if (!file)
			{
				return false;
			}
			u8 type[3];
			file->read(&type, sizeof(u8) * 3);
			return (type[2] == 2);
		}

		ISurface* CSurfaceLoaderTGA::loadImage(irr::io::IReadFile* file)
		{
			STGAHeader header;
			file->seek(0);
			file->read(&header, sizeof(STGAHeader));

			if (header.ImageType != 2)
			{
				return 0;
			}
			if (header.IdLength)
			{
				file->seek(header.IdLength, true);
			}
			if (header.ColorMapType != 0)
			{
				file->seek((header.ColorMapEntrySize / 8 * header.ColorMapLength), true);
			}
			
			s32 bytesPerPixel = header.PixelDepth / 8;
			s32 imageSize = header.ImageHeight * header.ImageWidth * bytesPerPixel;
			c8* data = new c8[imageSize];

			file->read(data, imageSize);

			video::ISurface* surface = video::createSurface(core::dimension2d<s32>(header.ImageWidth, header.ImageHeight));

			switch (bytesPerPixel)
			{
			case 1 :
				break;

			case 2:
			{
				s16* src = (s16*)((void*)data);
				s16* start = (s16*)((void*)surface->lock());
				s16* end = start + header.ImageWidth * header.ImageHeight - 1;
				for ( ; end > start; --end; ++src)
				{
					*end = *src;
				}
				surface->unlock();
			}
			break;

			case 3:
			{
				CColorConverter::convert24BitTo16BitFlipMirror(data, surface->lock(), header.ImageWidth, header.ImageHeight, 0, 0);
				surface->unlock();
			}
			break;

			case 4:
			{
				CColorConverter::convert32BitTo16BitFlipMirrorColorShuffle(data, surface->lock(), header.ImageWidth, header.ImageHeight, 0, 0);
				surface->unlock();
			}
			break;
					
			default:
				break;
			}


			delete[] data;
			return surface;
		}

		ISurfaceLoader* createSurfaceLoaderTGA()
		{
			return new CSurfaceLoaderTGA;
		}
	}
}