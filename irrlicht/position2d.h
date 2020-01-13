//ÒÑÍê³É
#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace core
	{
		template <class T>
		class position2d
		{
		public:
			T _x, _y;
			position2d(T x, T y)
			{
				_x = x;
				_y = y;
			}
			bool operator== (const position2d<T>& other) const
			{
				return _x == other._x && _y == other._y;
			}
			bool operator != (const position2d<T>& other) const
			{
				return _x != other._x || _y != other._y;
			}
			const positon2d<T>& operator += (const position2d<T>& other)
			{
				_x += other._x;
				_y += other._y;
				return *this;
			}
			const positon2d<T>& operator -= (const position2d<T>& other)
			{
				_x -= other._x;
				_y -= other._y;
				return *this;
			}
			position2d<T> operator- (const position2d<T>& other)const
			{
				return position2d<T>(_x - other._x, _y - other._y);
			}

			position2d<T> operator+ (const position2d<T>& other)const
			{
				return position2d<T>(_x + other._x, _y + other._y);
			}

			const position2d<T>& operator= (const position2d<T>& other)
			{
				_x = other._x;
				_y = other._y;
				return *this;
			}
		};
	}
}