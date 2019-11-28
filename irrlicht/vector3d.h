//ÒÑÍê³É

#pragma once
#include <math.h>
#include "irrtypes.h"

namespace irr
{
	namespace core
	{
		template< class T>
		class vector3d
		{
		public:
			T X, Y, Z;
			vector3d()
			{
				X = 0;
				Y = 0;
				Z = 0;
			}
			vector3d(T nx, T ny, T nz)
			{
				X = nx;
				Y = ny;
				Z = nz;
			}
			vector3d(const vector3d<T>& other)
			{
				X = other.X;
				Y = other.Y;
				Z = other.Z;
			}
			vector3d<T>& operator= (const vector3d<T>& other)
			{
				X = other.X;
				Y = other.Y;
				Z = other.Z;
				return *this;
			}
			vector3d<T>& operator+ (const vector3d<T>& other) const
			{
				return vector3d<T>(X + other.X, Y + other.Y, Z + other.Z);
			}
			vector3d<T>& operator+= (const vector3d<T>& other) 
			{
				X += other.X;
				Y += other.Y;
				Z += other.Z;
			}
			vector3d<T>& operator- (const vector3d<T>& other) const
			{
				return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z);
			}
			vector3d<T>& operator-= (const vector3d<T>& other)
			{
				X -= other.X;
				Y -= other.Y;
				Z -= other.Z;
			}
			vector3d<T>& operator* (const vector3d<T>& other) const
			{
				return vector3d<T>(X * other.X, Y * other.Y, Z * other.Z);
			}
			vector3d<T>& operator*= (const vector3d<T>& other)
			{
				X *= other.X;
				Y *= other.Y;
				Z *= other.Z;
			}
			vector3d<T> operator* (const T v) const
			{
				return vector3d<T>(X * v, Y * v, Z * v);

			}
			vector3d<T>& operator *= (const T v)
			{
				X *= v;
				Y *= v;
				Z *= v;
				return *this;
			}
			vector3d<T>& operator/ (const vector3d<T>& other) const
			{
				return vector3d<T>(X / other.X, Y / other.Y, Z / other.Z);
			}
			vector3d<T>& operator/= (const vector3d<T>& other)
			{
				X /= other.X;
				Y /= other.Y;
				Z /= other.Z;
			}
			vector3d<T> operator/ (const T v) const
			{
				T i = (T) 1.0 / v;
				return vector3d<T>(X * i, Y * i, Z * i);

			}
			vector3d<T>& operator /= (const T v)
			{
				T i = (T) 1.0 / v;
				X *= i;
				Y *= i;
				Z *= i;
				return *this;
			}

			bool operator <= (const vector3d<T>& other) const
			{
				return x <= other.X && Y <= other.Y && Z <= other.Z;
			}
			bool operator >= (const vector3d<T>& other) const
			{
				return x >= other.X && Y >= other.Y && Z >= other.Z;
			}
			bool operator == (const vector3d<T>& other) const
			{
				return x == other.X && Y == other.Y && Z == other.Z;
			}
			bool operator != (const vector3d<T>& other) const
			{
				return x != other.X || Y != other.Y || Z != other.Z;
			}

			void set(const T nx, const T ny, const T nz)
			{
				X = nx;
				Y = ny;
				Z = nz;
			}
			f64 getLength() const
			{
				return sqrt(X * X + Y * Y + Z * Z);
			}
			T dotProduct(const vector3d<T>& other)const
			{
				return X * other.X + Y * other.Y + Z * other.Z;
			}
			float getDistanceFrom(const vector3d<T>& other)
			{
				f64 vx = X - other.X;
				f64 vy = Y - other.Y;
				f64 vz = Z - other.Z;
				return sqrt(vx * vx + vy * vy + vz * vz);
			}
			vector3d<T> crossProduct(const vector3d<T>& p) const
			{
				return vector3d<T> (Y)
			}
			bool isBetweenPoints(const Vector3d<T>& begin, const vector3d<T>& end) const
			{
				vector3df lv = end - begin;
				vector3df pv = *this - begin;
				T l1 = lv.X * lv.X + lv.Y * lv.Y + lv.Z * lv.Z;
				T l2 = pv.X * pv.X + pv.Y * pv.Y + pv.Z * pv.Z;

				return l2 < l1;
			}
			void normalize()
			{
				T inv = (T) 1.0 / (T)getLength();
				X *= inv;
				Y *= inv;
				Z *= inv;
			}
			void invert()
			{
				X *= -1.0f;
				Y *= -1.0f;
				Z *= -1.0f;
			}
			void rotateXZBy(f64 degrees, const vector3d<T>& center)
			{
				degrees *= GRAD_PI2;
				T cs = (T)cos(degrees);
				T sn = (T)sin(degrees);
				X -= center.X;
				Z -= center.Z;
				set(X * cs - Z * sn, Y, X * sn + Z * cs);
				X += center.X;
				Z += center.Z;
			}
			void rotateXYBy(f64 degrees, const vector3d<T>& center)
			{
				degrees *= GRAD_PI2;
				T cs = (T)cos(degrees);
				T sn = (T)sin(degrees);
				X -= center.X;
				Y -= center.Y;
				set(X * cs - Y * sn,  X * sn + Y * cs, Z);
				X += center.X;
				Z += center.Z;
			}
			void rotateYZBy(f64 degrees, const vector3d<T>& center)
			{
				degrees *= GRAD_PI2;
				T cs = (T)cos(degrees);
				T sn = (T)sin(degrees);
				Z -= center.Z;
				Y -= center.Y;
				set(X, Y * cs - Z * sn, Y * sn + Z * cs);
				Y += center.Y;
				Z += center.Z;
			}
		};
		typedef vector3d<f32> vector3df;
		typedef vector3d<s32> vector3di;
	}
}