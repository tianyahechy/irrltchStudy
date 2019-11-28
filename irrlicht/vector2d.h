
//ÒÑÍê³É
#pragma once
#include <math.h>
#include "irrtypes.h"

namespace irr
{
	namespace core
	{
		template <class T>
		inline void rotateBy(f64 degrees, T& x, T& y, T centerX, T centerY)
		{
			degrees *= GRAD_PI2;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			X -= centerX;
			Y -= centerY;
			
			T nx = x * cs - y * sn;
			y = x * sn + y * cs;
			x = nx;

			X += centerX;
			Y += centerY;
		}
		template< class T>
		class vector2d
		{
		public:
			T X, Y;
			vector2d()
			{
				X = 0;
				Y = 0;
			}
			vector2d(T nx, T ny)
			{
				X = nx;
				Y = ny;
			}
			vector2d(const vector2d<T>& other)
			{
				X = other.X;
				Y = other.Y;
			}
			vector2d<T>& operator= (const vector2d<T>& other)
			{
				X = other.X;
				Y = other.Y;
				return *this;
			}
			vector2d<T>& operator+ (const vector2d<T>& other) const
			{
				return vector2d<T>(X + other.X, Y + other.Y);
			}
			vector2d<T>& operator+= (const vector2d<T>& other)
			{
				X += other.X;
				Y += other.Y;
				return *this;
			}
			vector2d<T>& operator- (const vector2d<T>& other) const
			{
				return vector2d<T>(X - other.X, Y - other.Y);
			}
			vector2d<T>& operator-= (const vector2d<T>& other)
			{
				X -= other.X;
				Y -= other.Y;
				return *this;
			}
			vector2d<T>& operator* (const vector2d<T>& other) const
			{
				return vector2d<T>(X * other.X, Y * other.Y);
			}
			vector2d<T>& operator*= (const vector2d<T>& other)
			{
				X *= other.X;
				Y *= other.Y;
				return *this;
			}
			vector2d<T> operator* (const T v) const
			{
				return vector2d<T>(X * v, Y * v);

			}
			vector2d<T>& operator *= (const T v)
			{
				X *= v;
				Y *= v;
				return *this;
			}
			vector2d<T>& operator/ (const vector2d<T>& other) const
			{
				return vector2d<T>(X / other.X, Y / other.Y);
			}
			vector2d<T>& operator/= (const vector2d<T>& other)
			{
				X /= other.X;
				Y /= other.Y;
				return *this;
			}
			vector2d<T> operator/ (const T v) const
			{
				T i = (T) 1.0 / v;
				return vector2d<T>(X * i, Y * i);

			}
			vector2d<T>& operator /= (const T v)
			{
				T i = (T) 1.0 / v;
				X *= i;
				Y *= i;
				return *this;
			}

			bool operator <= (const vector2d<T>& other) const
			{
				return x <= other.X && Y <= other.Y ;
			}
			bool operator >= (const vector2d<T>& other) const
			{
				return x >= other.X && Y >= other.Y;
			}
			bool operator == (const vector2d<T>& other) const
			{
				return x == other.X && Y == other.Y;
			}
			bool operator != (const vector2d<T>& other) const
			{
				return x != other.X || Y != other.Y;
			}

			void set(const T& nx, const T& ny)
			{
				X = nx;
				Y = ny;
			}
			void set(const vector2d<T>& p)
			{
				X = p.X;
				Y = p.Y;
			}
			f64 getLength() const
			{
				return sqrt(X * X + Y * Y);
			}
			T dotProduct(const vector2d<T>& other)const
			{
				return X * other.X + Y * other.Y;
			}
			float getDistanceFrom(const vector2d<T>& other)
			{
				f64 vx = X - other.X;
				f64 vy = Y - other.Y;
				return sqrt(vx * vx + vy * vy);
			}
		
			void normalize()
			{
				T inv = (T) 1.0 / (T)getLength();
				X *= inv;
				Y *= inv;
			}
		
			void rotateBy(f64 degrees, const vector2d<T>& center)
			{
				degrees *= GRAD_PI2;
				T cs = (T)cos(degrees);
				T sn = (T)sin(degrees);
				X -= center.X;
				Y -= center.Y;
				set(X * cs - Y * sn, X * sn + Y * cs);
				X += center.X;
				Y += center.Y;
			}
	
		};
		typedef vector2d<f32> vector2df;
		typedef vector2d<s32> vector2di;
	}
}