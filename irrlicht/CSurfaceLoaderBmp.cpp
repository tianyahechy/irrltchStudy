
#include "CSurfaceLoaderBmp.h"
#include <string.h>
#include "color.h"
#include "CColorConverter.h"

namespace irr
{
	namespace video
	{


		//! constructor
		CSurfaceLoaderBmp::CSurfaceLoaderBmp()
			: BmpData(0), PaletteData(0)
		{
#ifdef _DEBUG
			setDebugName("CSurfaceLoaderBMP");
#endif
		}



		//! destructor
		CSurfaceLoaderBmp::~CSurfaceLoaderBmp()
		{
			if (PaletteData)
				delete[] PaletteData;

			if (BmpData)
				delete[] BmpData;
		}



		//! returns true if the file maybe is able to be loaded by this class
		//! based on the file extension (e.g. ".tga")
		bool CSurfaceLoaderBmp::isALoadableFileExtension(const c8* fileName)
		{
			return strstr(fileName, ".bmp") != 0;
		}


		//! returns true if the file maybe is able to be loaded by this class
		bool CSurfaceLoaderBmp::isALoadableFileFormat(irr::io::IReadFile* file)
		{
			u16 headerID;
			file->read(&headerID, sizeof(u16));
			return headerID == 'MB';
		}

		void CSurfaceLoaderBmp::decompress8BitRLE(c8*& BmpData, s32 size, s32 width, s32 height, s32 pitch)
		{
			c8* p = BmpData;
			c8* newBmp = new c8[(width + pitch) * height];
			c8* d = newBmp;
			c8* destEnd = newBmp + (width + pitch) * height;
			s32	 line = 0;

			while (BmpData - p < size && d < destEnd)
			{
				if (* p == 0)
				{
					++p;
					switch (*p)
					{
					case 0:
						++p;
						++line;
						d = newBmp + line * (width + pitch);
						break;

					case 1:
						delete[] BmpData;
						BmpData = newBmp;
						return;

					case 2:
						++p;
						d += (u8)*p;
						++p;
						d += ((u8)*p) * (width + height);
						++p;
						break;

					default:
					{
						s32 count = (u8)*p;
						++p;
						s32 readAdditional((2 - (count % 2)) % 2);
						for (s32 i = 0; i < count; i++)
						{
							*d = *p;
							++p;
							++d;
						}
						for (int i = 0; i < readAdditional; i++)
						{
							++p;
						}

					}
					}
				}
				else
				{
					s32	count = (u8)*p;
					++p;
					s32 color = (u8)*p;
					++p;
					for (s32 i = 0; i < count; i++)
					{
						*d = color;
						++d;
					}
				}
			}
			delete[] BmpData;
			BmpData = newBmp;

		}
		void CSurfaceLoaderBmp::decompress4BitRLE(c8*& BmpData, s32 size, s32 width, s32 height, s32 pitch)
		{
			s32 lineWidth = (width + 1) / 2 + pitch;
			c8* p = BmpData;
			c8* newBmp = new c8[lineWidth * height];
			c8* d = newBmp;
			c8* destEnd = newBmp + lineWidth * height;
			s32	line = 0;
			s32 shift = 4;

			while (BmpData - p < size && d < destEnd)
			{
				if (*p == 0)
				{
					++p;
					switch (*p)
					{
					case 0:
						++p;
						++line;
						d = newBmp + line * lineWidth;
						shift = 4;
						break;

					case 1:
						delete[] BmpData;
						BmpData = newBmp;
						return;

					case 2:
						++p;
						s32 x = (u8)*p;
						++p;
						s32 y = (u8)*p;
						++p;
						d += x / 2 + y * lineWidth;
						shift = x % 2 == 0 ? 4 : 0;
						break;

					default:
					{
						s32 count = (u8)*p;
						++p;
						s32 readAdditional((2 - (count % 2)) % 2);
						s32 readShift = 4;
						for (s32 i = 0; i < count; i++)
						{
							s32 color = (((u8)*p) >> readShift) & 0x0f;
							readShift -= 4;
							if (readShift < 0)
							{
								++* p;
								readShift = 4;
							}
							c8 mask = 0x0f << shift;
							*d = (*d & (~mask)) | ((color << shift) & mask);
							shift -= 4;
							if (shift < 0)
							{
								shift = 4;
								++d;
							}
						}
						for (int i = 0; i < readAdditional; i++)
						{
							++p;
						}

					}
					}
				}
				else
				{
					s32	count = (u8)*p;
					++p;
					s32 color = (u8)*p;
					++p;
					for (s32 i = 0; i < count; i++)
					{
						*d = color;
						++d;
					}
				}
			}
			delete[] BmpData;
			BmpData = newBmp;

		}

		ISurface* CSurfaceLoaderBmp::loadImage(irr::io::IReadFile* file)
		{
			SBMPHeader header;
			file->seek(0);
			file-> read(&header, sizeof(header));
			s32 pitch = 0;
			if (header.Id != 'MB' && header.Id != 'BM')
			{
				return 0;
			}
			if (header.Compression > 2)
			{
				return 0;
			}
			header.BitmapDataSize += (4 - (header.BitmapDataSize % 4)) % 4;

			s32 pos = file->getPos();
			s32 paletteSize = (header.BitmapDataOffset - pos) / 4;
			if (paletteSize)
			{
				PaletteData = new s32[paletteSize];
				file->read(PaletteData, paletteSize * sizeof(s32));
			}
			if (!header.BitmapDataSize)
			{
				header.BitmapDataSize = file->getSize() - header.BitmapDataOffset;
			}
			file->seek(header.BitmapDataOffset);
			f32 t = (header.Width) * (header.BPP / 8.0);
			s32 widthInBytes = (s32)t;
			t -= widthInBytes;
			if (t != 0.0f)
			{
				++widthInBytes;
			}
			s32 lineData = widthInBytes + ((4 - (widthInBytes % 4))) % 4;
			pitch = lineData - widthInBytes;
			BmpData = new c8[header.BitmapDataSize];
			file->read(BmpData, header.BitmapDataSize);

			switch (header.Compression)
			{
			case 1:
				this->decompress8BitRLE(BmpData, header.BitmapDataSize, header.Width, header.Height, pitch);
				break;

			case 2:
				this->decompress4BitRLE(BmpData, header.BitmapDataSize, header.Width, header.Height, pitch);
				break;

			default:
				break;
			}

			ISurface* surface = createSurface(core::dimension2d<s32>(header.Width, header.Height));
			switch (header.BPP)
			{
			case 1:
				CColorConverter::convert1BitTo16BitFlipMirror(BmpData, surface->lock(), header.Width, header.Height, pitch, PaletteData);
				surface->unlock();
				break;

			case 4:
				CColorConverter::convert4BitTo16BitFlipMirror(BmpData, surface->lock(), header.Width, header.Height, pitch, PaletteData);
				surface->unlock();
				break;

			case 8:
				CColorConverter::convert8BitTo16BitFlipMirror(BmpData, surface->lock(), header.Width, header.Height, pitch, PaletteData);
				surface->unlock();
				break;

			case 16:
				break;

			case 24:
				CColorConverter::convert24BitTo16BitFlipMirror(BmpData, surface->lock(), header.Width, header.Height, pitch, PaletteData);
				surface->unlock();
				break;

			case 32:
				break;

			default:
				break;
			}
			delete[] PaletteData;
			PaletteData = 0;

			delete[] BmpData;
			BmpData = 0;
			return surface;
		}

		ISurfaceLoader* createSurfaceloaderBMP()
		{
			return new CSurfaceLoaderBmp;
		}
	}
}