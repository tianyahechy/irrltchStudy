//ÒÑÍê³É

#pragma once
#include "irrtypes.h"
#include "plane3dex.h"
namespace irr
{
	namespace core
	{
		template <class T>
		class aabbox3d
		{
			vector3d<T> _minEdge;
			vector3d<T> _maxEdge;

			aabbox3d()
			{
				_minEdge = vector3d<T>(-1, -1, -1);
				_maxEdge = vector3d<T> ( 1, 1, 1);
			}
			aabbox3d(const vector3d<T>& min, const vector3d<T>& max)
			{
				_minEdge = min;
				_maxEdge = max;
			}
			aabbox3d(T minx, T miny, T minz, T maxx, T maxy, T maxz)
			{
				_minEdge = vector3d<T>(minx, miny, minz);
				_maxEdge = vector3d<T>(maxx, maxy, maxz);
			}

			inline bool operator== (const aabbox3d<T>& other) const
			{
				return (_minEdge == other._minEdge && other._maxEdge == _maxEdge);
			}
			inline bool operator!= (const aabbox3d<T>& other) const
			{
				return !(_minEdge == other._minEdge && other._maxEdge == _maxEdge);
			}
			void addInternalPoint(T x, T y, T z)
			{
				if (x > _maxEdge.X)
				{
					_maxEdge.X = x;
				}
				if ( y > _maxEdge.Y)
				{
					_maxEdge.Y = y;
				}
				if (z > _maxEdge.Z)
				{
					_maxEdge.Z = z;
				}
				if ( x < _minEdge.X)
				{
					_minEdge.X = x;
				}
				if (y < _minEdge.Y)
				{
					_minEdge.Y = y;
				}
				if (z < _minEdge.Z)
				{
					_minEdge.Z = z;
				}
			}

			void addInternalPoint(const vector3d<T>& p)
			{
				addInternalPoint(p.X, p.Y, p.Z);
			}
			void addInternalBox(const aabbox3d<T> &b)
			{
				addInternalPoint(b._maxEdge);
				addInternalPoint(b._minEdge);
			}
			void reset(T x, T y, T z)
			{
				_maxEdge.set(x, y, z);
				_minEdge = _maxEdge;
			}
			void reset(const vector3d<T>& initValue)
			{
				_maxEdge = initValue;
				_minEdge = initValue;
			}
			bool isPointInside(const vector3d<T>& p) const
			{
				return (p.X >= _minEdge.X && p.X <= _maxEdge.X &&
					p.Y >= _minEdge.Y && p.Y <= _maxEdge.Y &&
					p.Z >= _minEdge.Z && p.Z <= _maxEdge.Z 
					);
			}
			bool isPointTotalInside(const vector3d<T>& p) const
			{
				return (p.X > _minEdge.X && p.X < _maxEdge.X &&
					p.Y > _minEdge.Y && p.Y < _maxEdge.Y &&
					p.Z > _minEdge.Z && p.Z < _maxEdge.Z
					);
			}
			bool intersectsWithBox(const aabbox3d<T>& other) const
			{
				return (_minEdge <= other._maxEdge && _maxEdge >= other._minEdge);
			}
			EIntersectionRelation3D classifyPlaneRelation(const plane3dex<f32>& plane) const
			{
				vector3d<T> nearPoint(_maxEdge);
				vector3d<T> farPoint(_minEdge);
				if (plane._Normal.X > (T) 0)
				{
					nearPoint.X = _minEdge.X;
					farPoint.X = _maxEdge.X;
				}
				if (plane._Normal.Y > (T)0)
				{
					nearPoint.Y = _minEdge.Y;
					farPoint.Y = _maxEdge.Y;
				}
				if (plane._Normal.Z > (T)0)
				{
					nearPoint.Z = _minEdge.Z;
					farPoint.Z = _maxEdge.Z;
				}
				if (plane._Normal.dotProduct(nearPoint) + plane._D > (T) 0 )
				{
					return ISREL3D_FRONT;
				}
				if (plane._Normal.dotProduct(farPoint) + plane._D > (T)0)
				{
					return ISREL3D_CLIPPED;
				}
				return ISREL3D_BACK;

			}
		};
	}
}
