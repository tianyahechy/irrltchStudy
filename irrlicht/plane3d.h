//ÒÑÍê³É
#pragma once
#include "irrmath.h"
#include "vector3d.h"

namespace irr
{
	namespace core
	{
		enum EIntersectionRelation3D
		{
			ISREL3D_FRONT = 0,
			ISREL3D_BACK,
			ISREL3D_PLANAR,
			ISREL3D_SPANNING,
			ISREL3D_CLIPPED

		};
		template <class T>
		class plane3d
		{
		public:
			vector3d<T> _MPoint;
			vector3d<T> _Normal;

			plane3d()
			{
				_MPoint = vector3d<T>(0, 0, 0);
				_Normal = vector3d<T>(0, 1, 0);

			}
			plane3d(const vector3d<T>& MPoint, const vector3d<T>& Normal) :
			{
				_MPoint = MPoint;
				_Normal = Normal;
			}
			plane3d(T px, T py, T pz, T nx, T ny, T nz)
			{
				_MPoint = vector3d<T>(px, py, pz);
				_Normal = vector3d<T>(nx, ny, nz);
			}
			plane3d(const plane3d<T>& other)
			{
				_MPoint = other._MPoint;
				_Normal = other._Normal;
			}
			plane3d(
				const vector3d<T>& point1,
				const vector3d<T>& point2,
				const vector3d<T>& point3
			)
			{
				setPlane(point1, point2, point3);
			}

			inline bool operator == (const plane3d<T>& other) const
			{
				return (_MPoint == other._MPoint && _Normal == other._Normal);
			}
			inline bool operator != (const plane3d<T>& other) const
			{
				return !(_MPoint == other._MPoint && _Normal == other._Normal);
			}
			void setPlane(const vector3d<T>& point, const vector3d<T>& nvector)
			{
				_Normal = nvector;
				_Normal.normalize();
				_MPoint = point;
			}
			void setPlane(const vector3d<T>& point1, const vector3d<T>& point2, const vector3d<T>& point3)
			{
				_Normal = (point2 - point1).crossProduct(point3 - point1);
				_Normal.normalize();
				_MPoint = point1;
			}

			bool getIntersectionWithLine(const vector3d<T>& linePoint, const vector3d<T>& lineVect, vector3d<T>& outIntersection) const
			{
				T t2 = _Normal.dotProduct(lineVect);
				if ( 0 == t2)
				{
					return false;
				}
				T t = -(_Normal.dotProduct(linePoint) - _MPoint.dotProduct(_Normal)) / t2;
				outIntersection = linePoint + lineVect * t;
				return true;
			}
			bool getIntersectionWithLimitedLine(const vector3d<T>& linePoint1, const vector3d<T>& linePoint2, vector3d<T>& outIntersection) const
			{
				return getIntersectionWithLine(linePoint1, linePoint2 - linePoint1, outIntersection) && outIntersection.isBetweenPoints(linePoint1, linePoint2));
			}
			EIntersectionRelation3D classifyPointRelation(const vector3d<T>& point) const
			{
				f32 pktprd = (_MPoint - point).dotProduct(_Normal);
				if (pktprd < - ROUNDING_ERROR)
				{
					return ISREL3D_FRONT;
				}
				if (pktprd > ROUNDING_ERROR)
				{
					return ISREL3D_BACK;
				}
				return ISREL3D_PLANAR;
			}
		};
	}
}
