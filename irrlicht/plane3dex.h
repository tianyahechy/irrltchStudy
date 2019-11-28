
//ÒÑÍê³É
#pragma once
#include "irrtypes.h"
#include "plane3d.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class plane3dex
		{
		public:
			T _D;
			vector3d<T> _MPoint;
			vector3d<T> _Normal;

			void recalculatedD()
			{
				_D = -_MPoint.dotProduct(_Normal);
			}
			plane3dex()
			{
				_MPoint = vector3d<T>(0, 0, 0);
				_Normal = vector3d<T>(0, 1, 0);
				recalculatedD();

			}
			plane3dex(const vector3d<T>& MPoint, const vector3d<T>& Normal) :
			{
				_MPoint = MPoint;
				_Normal = Normal;
				recalculatedD();
			}
			plane3dex(T px, T py, T pz, T nx, T ny, T nz)
			{
				_MPoint = vector3d<T>(px, py, pz);
				_Normal = vector3d<T>(nx, ny, nz);
				recalculatedD();
			}
			plane3dex(const plane3dex<T>& other)
			{
				_MPoint = other._MPoint;
				_Normal = other._Normal;
				recalculatedD();
			}
			plane3dex(
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
			inline bool operator == (const plane3dex<T>& other) const
			{
				return (_MPoint == other._MPoint && _Normal == other._Normal);
			}
			inline bool operator != (const plane3dex<T>& other) const
			{
				return !(_MPoint == other._MPoint && _Normal == other._Normal);
			}
			void setPlane(const vector3d<T>& point, const vector3d<T>& nvector)
			{
				_Normal = nvector;
				_Normal.normalize();
				_MPoint = point;
				recalculatedD();
			}
			void setPlane(const vector3d<T>& point1, const vector3d<T>& point2, const vector3d<T>& point3)
			{
				_Normal = (point2 - point1).crossProduct(point3 - point1);
				_Normal.normalize();
				_MPoint = point1;
				recalculatedD();
			}

			bool getIntersectionWithLine(const vector3d<T>& linePoint, const vector3d<T>& lineVect, vector3d<T>& outIntersection) const
			{
				T t2 = _Normal.dotProduct(lineVect);
				if (0 == t2)
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
				if (pktprd < -ROUNDING_ERROR)
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
