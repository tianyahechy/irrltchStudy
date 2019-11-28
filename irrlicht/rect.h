
//ÒÑÍê³É
#pragma once
#include "irrtypes.h"
#include "dimension2d.h"
#include "position2d.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class rect
		{
		public:
			dimension2d<T> _dimension;
			position2d<T> _position;

			rect()
			{
				_dimension = dimension2d<T>(0, 0);
				_position = position2d<T>(0, 0);
			}
			rect(T x, T y, T w, T h)
			{
				_dimension = dimension2d<T>(w, h);
				_position = position2d<T>(x, y);
			}
			rect(const rect<T>& other)
			{
				_dimension = other._dimension;
				_position = other._position;
			}
			rect(const position2d<T>& pos, const dimension2d<T>& dim)
			{
				_position = pos;
				_dimension = dim;
			}
			bool operator== (const rect<T>& other) const
			{
				return _dimension == other._dimension && _position == other._position;
			}
			bool operator != (const rect<T>& other) const
			{
				return _dimension != other._dimension || _position != other._position;
			}
			const rect<T>& operator= (const rect<T>& other)
			{
				_dimension = other._dimension;
				_position = other._position;
				return *this;
			}
			bool isPointInSide(const position2d<T>& pos) const
			{
				return _position._x <= pos._x && _position._y <= pos._y && _dimension._width + _position._x >= pos._x && _dimension._height + _position._y >= pos._y;
			}
		};
		template <class T>
		class rectEx
		{
		public:
			position2d<T> _upperLeftCorner;
			position2d<T> _lowerRightCorner;

			rectEx()
			{
				_upperLeftCorner = position2d<T>(0, 0);
				_lowerRightCorner = position2d<T>(0, 0);
			}
			rectEx(T x, T y, T x2, T y2)
			{
				_upperLeftCorner = position2d<T>(x, y);
				_lowerRightCorner = position2d<T>(x2, y2);
			}
			rectEx(const position2d<T>& upperLeft, const position2d<T>& lowerRight)
			{
				_upperLeftCorner = upperLeft;
				_lowerRightCorner = lowerRight;
			}
			rectEx(const rect<T>& other)
			{
				_upperLeftCorner = other._position;
				_lowerRightCorner = rectEx(other._position._x + other._dimension._width, other._position._y + other._dimension._height);
			}
			rectEx(const rectEx<T>& other)
			{
				_upperLeftCorner = other._upperLeftCorner;
				_lowerRightCorner = other._lowerRightCorner;
			}
			rectEx(const position2d<T>& pos, const dimension2d<T>& size)
			{
				_upperLeftCorner = pos;
				_lowerRightCorner = dimension2d<T>(pos._x + size._width, pos._y + size._height);
			}
			rectEx<T> operator+ (const position2d<T>& pos) const
			{
				rectEx<T> ret(*this);
				ret._upperLeftCorner += pos;
				ret._lowerRightCorner += pos;
				return ret;
			}
			
			const rectEx<T> operator += (const position2d<T> pos)
			{
				_upperLeftCorner += pos;
				_lowerRightCorner += pos;
				return *this;
			}

			bool operator == (const rectEx<T>& other) const
			{
				return _upperLeftCorner == other._upperLeftCorner && _lowerRightCorner == other._lowerRightCorner;
			}
			bool operator != (const rectEx<T>& other) const
			{
				return _upperLeftCorner != other._upperLeftCorner || _lowerRightCorner != other._lowerRightCorner;
			}
			const rectEx<T>& operator= (const rectEx<T>& other)
			{
				_upperLeftCorner = other._upperLeftCorner;
				_lowerRightCorner = other._lowerRightCorner;
				return *this;
			}
			bool isPointInSide(const position2d<T>& pos) const
			{
				return _upperLeftCorner._x <= pos._x && _upperLeftCorner._y <= pos._y &&
					_lowerRightCorner._x >= pos._x && _lowerRightCorner._y >= pos._y;
			}
			bool isRectCollide(const rectEx<T>& other) const
			{
				return (_lowerRightCorner._y > other._upperLeftCorner._y && _upperLeftCorner._y < other._lowerRightCorner._y &&
					_lowerRightCorner._x > other._upperLeftCorner._x && _upperLeftCorner._x < other._lowerRightCorner._x);
			}
			void clipAgainst(const rectEx<T>& other)
			{
				if (other._lowerRightCorner._x < _lowerRightCorner._x)
				{
					_lowerRightCorner._x = other._lowerRightCorner._x;
				}
				if (other._lowerRightCorner._y < _lowerRightCorner._y)
				{
					_lowerRightCorner._y = other._lowerRightCorner._y;
				}
				if (other._upperLeftCorner._x > _upperLeftCorner._x)
				{
					_upperLeftCorner._x = other._upperLeftCorner._x;
				}
				if (other._upperLeftCorner._y > _upperLeftCorner._y)
				{
					_upperLeftCorner._y = other._upperLeftCorner._y;
				}
			}
			T getWidth() const
			{
				return _lowerRightCorner._x - _upperLeftCorner._x;
			}
			T getHeight() const
			{
				return _lowerRightCorner._y - _upperLeftCorner._y;
			}
			void repair()
			{
				if (_lowerRightCorner._x < _upperLeftCorner._x)
				{
					s32 t = _lowerRightCorner._x;
					_lowerRightCorner._x = _upperLeftCorner._x;
					_upperLeftCorner._x = t;
				}
				if (_lowerRightCorner._y < _upperLeftCorner._y)
				{
					s32 t = _lowerRightCorner._y;
					_lowerRightCorner._y = _upperLeftCorner._y;
					_upperLeftCorner._y = t;
				}
			}
		};
	}
}
