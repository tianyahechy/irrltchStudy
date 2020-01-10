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
	}
}
