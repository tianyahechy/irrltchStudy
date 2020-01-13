#include "CSurface.h"
#include <memory.h>
#include "color.h"

namespace irr
{
	namespace video
	{
		CSurface::CSurface(const core::dimension2d<s32>& size)
		{
			_size = size;
			_dataSize = _size._width * _size._height;
			_dataSizeInBytes = _dataSize * sizeof(s16);
			_data = new s16[_dataSize];
		}
		CSurface::~CSurface()
		{
			delete[] _data;
		}
		s16 * CSurface::lock()
		{
			return _data;
		}
		void CSurface::unlock()
		{
		}
		const core::dimension2d<s32>& CSurface::getDimension()
		{
			// TODO: 在此处插入 return 语句
			return _size;
		}

		s16 CSurface::getPixel(s32 x, s32 y)
		{
			if ( x < 0 || y < 0 || x > _size._width || y > _size._height)
			{
				return 0;
			}
			return _data[y*_size._width + x];
		}
		void CSurface::setPixel(s32 x, s32 y, s16 color)
		{
			clipX(x);
			clipY(y);
			_data[y * _size._width + x] = color;
		}
		inline void CSurface::setPixelFast(s32 x, s32 y, s16 color)
		{
			_data[y * _size._width + x] = color;
		}
		s16 CSurface::getRedMask()
		{
			return 0x1F << 10;
		}
		s16 CSurface::getGreenMask()
		{
			return 0x1F << 5;
		}
		s16 CSurface::getBlueMask()
		{
			return 0x1F;
		}
		s16 CSurface::getAlphaMask()
		{
			return (s16)(0x1 << 15);
		}
		void CSurface::fill(s16 color)
		{
			s32 * p = (s32*)_data;
			s32 * bufferEnd = p + (_dataSize >> 1);
			s32 c = ((color & 0x0000ffff) << 16) | (color & 0x0000ffff);
			while ( p != bufferEnd)
			{
				*p = c;
				++p;
			}
		}
		inline void CSurface::clipX(s32& x)
		{
			if (x < 0)
			{
				x = 0;
			}
			else if ( x > _size._width)
			{
				x = _size._width;
			}
		}
		inline void CSurface::clipY(s32& y)
		{
			if ( y < 0)
			{
				y = 0;
			}
			else if ( y > _size._height)
			{
				y = _size._height;
			}
		}
		inline void CSurface::exchange(s32& a, s32& b)
		{
			s32 tmp = a;
			a = b;
			b = tmp;
		}
		void CSurface::drawRectangle(const core::rectEx<s32>& rect, Color theColor)
		{
			drawRectangle(rect._upperLeftCorner._x, rect._upperLeftCorner._y,
				rect._lowerRightCorner._x, rect._lowerRightCorner._y, theColor);
		}
	}
}
