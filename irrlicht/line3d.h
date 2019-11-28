//ÒÑÍê³É

#pragma once
#include <math.h>
#include "irrtypes.h"
#include "vector3d.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class line3d
		{
		public:
			vector3d<T> _start;
			vector3d<T> _end;

			line3d()
			{
				_start = vector3d(0, 0, 0);
				_end = vector3d(1, 1, 1);
			}
			line3d(T xa, T ya, T za, T xb, T yb, T zb)
			{
				_start = vector3d(xa, ya, za);
				_end = vector3d(xb, yb, zb);
			}
			line3d(const vector3d<T>& start, const vector3d<T>& end)
			{
				_start = start;
				_end = end;
			}
			line3d(const line3d<T>& other)
			{
				_start = other._start;
				_end = other._end;
			}
			line3d<T> operator+ (const vector3d<T>& point) const
			{
				return line3d<T>(_start + point, _end + point);
			}
			line3d<T> operator+= (const vector3d<T>& point)
			{
				_start += point;
				_end += point;
				return *this;
			}
			line3d<T> operator- (const vector3d<T>& point) const
			{
				return line3d<T>(_start - point, _end - point);
			}
			line3d<T> operator-= (const vector3d<T>& point)
			{
				_start -= point;
				_end -= point;
				return *this;
			}
			bool operator== (const line3d<T>& other) const
			{
				return (_start == other._start && _end == other._end) || (_end == other._start && _start == other._end);
			}

			bool operator!= (const line3d<T>& other) const
			{
				return !(_start == other._start && _end == other._end) || (_end == other._start && _start == other._end);
			}
			void setLine(const T& xa, const T& ya, const T& za, const T& xb, const T& yb, const T& zb)
			{
				_start.set(xa, ya, za);
				_end.set(xb, yb, zb);
			}
			void setLine(const vector3d<T>& nstart, const vector3d<T>& nend)
			{
				_start.set(nstart);
				_end.set(nend);
			}
			void setLine(const line3d<T>& line)
			{
				_start.set(line._start);
				_end.set(line._end);
			}
			f64 getLength()
			{
				return _start.getDistanceFrom(_end);
			}
		};

	}
}