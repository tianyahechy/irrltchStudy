#include "CSurfaceLoaderBmp.h"
#include <string.h>
#include "color.h"
#include "CColorConverter.h"

namespace irr
{
	namespace video
	{
		void CSurfaceLoaderBmp::decompres8BitRLE(c8 * bmpData, s32 size, s32 width, s32 height, s32 pitch)
		{
			c8 * p = bmpData;
			c8 * newBmp = new c8[(width + pitch) * height];
			c8 * d = newBmp;
			c8 * destEnd = newBmp + (width + pitch) * height;
			s32 line = 0;
			while (_bmpData - p < size && )
			{

			}

		}
		CSurfaceLoaderBmp::CSurfaceLoaderBmp()
		{
			_bmpData = 0;
			_paletteData = 0;
		}
		CSurfaceLoaderBmp::~CSurfaceLoaderBmp()
		{
			if (_bmpData)
			{
				delete[] _bmpData;
			}
			if (_paletteData)
			{
				delete[] _paletteData;
			}
		}
		bool CSurfaceLoaderBmp::isALoadableFileExtension(const c8 * fileName)
		{
			return strstr(fileName, ".bmp") != 0;
		}

		bool CSurfaceLoaderBmp::isALoadableFileFormat(irr::io::IReadFile * file)
		{
			u16 headerID;
			file->read(&headerID, sizeof(u16));
			return headerID == 'MB';
		}
		
	}
}