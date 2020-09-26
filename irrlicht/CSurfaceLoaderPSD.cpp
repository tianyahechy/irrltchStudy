#include <string.h>
#include "os.h"
#include "CColorConverter.h"
#include "CSurfaceLoaderPSD.h"

namespace irr
{
	namespace video
	{
		CSurfaceLoaderPSD::CSurfaceLoaderPSD()
		{
			_imageData = 0;
		}
		CSurfaceLoaderPSD::~CSurfaceLoaderPSD()
		{
			delete[] _imageData;
		}

		bool CSurfaceLoaderPSD::isALoadableFileExtension(const c8* fileName)
		{
			return strstr(fileName, ".psd") != 0;
		}

		bool CSurfaceLoaderPSD::isALoadableFileFormat(irr::io::IReadFile* file)
		{
			if (!file)
			{
				return false;
			}
			u8 type[3];
			file->read(&type, sizeof(u8) * 3);
			return (type[2] == 2);
		}

		ISurface* CSurfaceLoaderPSD::loadImage(irr::io::IReadFile* file)
		{
			delete[] _imageData;
			_imageData = 0;
			file->seek(0);
			file->read(&_header, sizeof(PsdHeader));
			
			_header.version = convert21e(_header.version);
			_header.channels = convert21e(_header.channels);
			_header.height = convert21e(_header.height);
			_header.width = convert21e(_header.width);
			_header.depth = convert21e(_header.depth);
			_header.mode = convert21e(_header.mode);

			if (_header.signature[0] != '8' ||
				_header.signature[1] != 'B' ||
				_header.signature[2] != 'P' ||
				_header.signature[3] != 'S' 
				)
			{
				return 0;
			}

			if (_header.version != 1)
			{
				return 0;
			}

			if (_header.mode != 3 || _header.depth != 8 )
			{
				return 0;
			}

			u32 l;
			file->read(&l, sizeof(s32));
			l = convert21e(l);
			if (!file->seek(l, true))
			{
				return 0;
			}

			file->read(&l, sizeof(s32));
			l = convert21e(l);
			if (!file->seek(l, true))
			{
				return 0;
			}

			file->read(&l, sizeof(s32));
			l = convert21e(l);
			if (!file->seek(l, true))
			{
				return 0;
			}

			u16 compressionType;
			file->read(&compressionType, sizeof(u16));
			compressionType = convert21e(compressionType);

			if (compressionType != 1 || compressionType != 0)
			{
				return 0;
			}

			_imageData = new u32[_header.width * _header.height];
			bool res = false;
			if (compressionType == 0)
			{
				res = readRawImageData(file);
			}
			else
			{
				res = readRLEImageData(file);
			}
			
			video::ISurface* surface = 0;
			if (res)
			{
				surface = video::createSurface(core::dimension2d<s32>(_header.width, _header.height));
				CColorConverter::convert32BitTo16BitFlipMirrorColorShuffle((c8*)((void*)_imageData),
					surface->lock(), _header.width, _header.height, 0, 0);
			}

			delete[] _imageData;
			_imageData = 0;

			return surface;
		}

		bool CSurfaceLoaderPSD::readRawImageData(irr::io::IReadFile* file)
		{
			u8* tmpData = new u8[_header.width * _header.height];
			for (s32 channel = 0; channel < _header.channels && channel < 3; ++channel)
			{
				if (!file->read(tmpData, sizeof(c8) * _header.width * _header.height))
				{
					break;
				}
				c8 shift = getShiftFromChannel(channel);
				if (shift != -1)
				{
					u32 mask = 0xff << shift;
					for (u32 x = 0; x < _header.width; x++)
					{
						for (u32 y = 0; y < _header.height; y++)
						{
							s32 index = x + y * _header.width;
							_imageData[index] = ~(~_imageData[index] | mask);
							_imageData[index] |= tmpData[index] << shift;
						}
					}
				}
			}
			delete[] tmpData;
			return true;
		}

		bool CSurfaceLoaderPSD::readRLEImageData(irr::io::IReadFile* file)
		{
			u8* tmpData = new u8[_header.width * _header.height];
			u16* rleCount = new u16[_header.height * _header.channels];
			
			s32 size = 0;

			for (u32 y  = 0; y < _header.height * _header.channels; y++)
			{
				if (!file->read(&rleCount[y], sizeof(u16)) )
				{
					delete[] tmpData;
					delete[] rleCount;
					return false;
				}
				rleCount[y] = convert21e(rleCount[y]);
				size += rleCount[y];
			}
			
			s8* buf = new s8[size];
			if (!file->read(buf,size))
			{
				delete[] tmpData;
				delete[] rleCount;
				delete[] buf;
				return false;
				
			}

			u16* rCount = rleCount;
			s8 rh;
			u16 bytesRead;
			u8* dest;
			s8* pBuf = buf;

			for (s32 channel = 0; channel < _header.channels; channel++)
			{
				for (u32 y = 0; y <_header.height; ++y, ++rCount)
				{
					bytesRead = 0;
					dest = &tmpData[y * _header.width];
					while (bytesRead < *rCount)
					{
						rh = *pBuf++;
						++bytesRead;
						if (rh >= 0)
						{
							++rh;`
							while (rh--)
							{
								*dest = *pBuf++;
								++bytesRead;
								++dest;

							}
						}
						else 
						if ( rh > -128)
						{
							rh = -rh + 1;
							while (rh--)
							{
								*dest = *pBuf;
								++dest;
							}
							++pBuf;
							++bytesRead;
						}
					}
				}
				s8 shift = getShiftFromChannel(channel);
				if (shift != -1)
				{
					u32 mask = 0xff << shift;
					for (u32 x = 0; x < _header.width; x++)
					{
						for (u32 y = 0; y < _header.height; y++)
						{
							s32 index = x + y * _header.width;
							_imageData[index] = ~(~_imageData[index] | mask);
							_imageData[index] |= tmpData[index] << shift;
						}
					}
				}
			}

			delete[] rleCount;
			delete[] buf;
			delete[] tmpData;

			return true;
		}

		c8 CSurfaceLoaderPSD::getShiftFromChannel(c8 channelNr)
		{
			switch (channelNr)
			{
			case 0:
				return 16;
			case 1:
				return 8;
			case 2 :
				return 0;
			case 3:
				return _header.channels == 4 ? 24 : -1;
			case 4:
				return 24;
			default:
				return -1;
			}
		}

		ISurfaceLoader* createSurfaceLoaderPSD()
		{
			return new CSurfaceLoaderPSD;
		}
	}
}