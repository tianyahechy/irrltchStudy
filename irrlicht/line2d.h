
//ÒÑÍê³É
#pragma once
#include <math.h>
#include "irrtypes.h"
#include "vector2d.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class line2d
		{
		public:
			vector2d<T> _start;
			vector2d<T> _end;

			line2d()
			{
				_start = vector2d(0, 0);
				_end = vector2d(1, 1);
			}
			line2d(T xa, T ya,T xb, T yb)
			{
				_start = vector2d(xa, ya);
				_end = vector2d(xb, yb);
			}
			line2d(const vector2d<T>& start, const vector2d<T>& end)
			{
				_start = start;
				_end = end;
			}
			line2d(const line2d<T>& other)
			{
				_start = other._start;
				_end = other._end;
			}
			line2d<T> operator+ (const vector2d<T>& point) const
			{
				return line2d<T>(_start + point, _end + point);
			}
			line2d<T> operator+= (const vector2d<T>& point)
			{
				_start += point;
				_end += point;
				return *this;
			}
			line2d<T> operator- (const vector2d<T>& point) const
			{
				return line2d<T>(_start - point, _end - point);
			}
			line2d<T> operator-= (const vector2d<T>& point)
			{
				_start -= point;
				_end -= point;
				return *this;
			}
			bool operator== (const line2d<T>& other) const
			{
				return (_start == other._start && _end == other._end) || (_end == other._start && _start == other._end);
			}

			bool operator!= (const line2d<T>& other) const
			{
				return !(_start == other._start && _end == other._end) || (_end == other._start && _start == other._end);
			}
			void setLine(const T& xa, const T& ya, const T& xb, const T& yb)
			{
				_start.set(xa, ya);
				_end.set(xb, yb);
			}
			void setLine(const vector2d<T>& nstart, const vector2d<T>& nend)
			{
				_start.set(nstart);
				_end.set(nend);
			}
			void setLine(const line2d<T>& line)
			{
				_start.set(line._start);
				_end.set(line._end);
			}
			f64 getLength()
			{
				return _start.getDistanceFrom(_end);
			}
			vector2d<T> getVector() const
			{
				return vector2d<T>(_start.X - _end.X, _start.Y - _end.Y);
			}

			bool intersectWith(const line2d<T>& l, vector2d<T>& out)
			{
				return false;
			}
			vector2d<T> getUnitVector()
			{
				T len = (T) 1.0 / (T)getLength();
				return vector2d<T>((_end.X - _start.X) * len, (_end.Y - _start.Y) * len);
			}
			f64 getAngleWith(const line2d<T> & l)
			{
				vector2d<T> vect = getVector();
				vector2d<T> vect2 = l.getVector();
			
				return vectorAngle(vect.X, vect.Y, vect2.X, vect2.Y);
			}
		};

	}
}