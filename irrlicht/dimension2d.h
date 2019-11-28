//ÒÑÍê³É

#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace core
	{
		template <class T>
		class dimension2d
		{
			T _width, _height;
		public:
			dimension2d()
			{
				_width = 0;
				_height = 0;
			}
			dimension2d(T width, T height)
			{
				_width = width;
				_height = height;
			}
			dimension2d(const dimension2d<T> & other)
			{
				_width = other._width;
				_height = other._height;
			}
			bool operator== (const dimension2d<T>& other) const
			{
				return _width == other._width && _height == other._height;
			}
			bool operator != (const dimension2d<T>& other) const
			{
				return _width != other._width || _height != other._height;
			}
			const dimension2d<T> & operator= (const dimension2d<T>& other)
			{
				_width = other._width;
				_height = other._height;
				return *this;
			}
		};
	}
}