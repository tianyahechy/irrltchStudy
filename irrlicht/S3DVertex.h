#pragma once
#include "vector2d.h"
#include "vector3d.h"
#include "color.h"

namespace irr
{
	namespace video
	{
		enum E_VERTEX_TYPE
		{
			EVT_STANDARD = 0,
			EVT_2TCOORDS
		};

		struct S3DVertex
		{
			core::vector3df _pos;
			core::vector3df _normal;
			video::Color _color;
			core::vector2d<f32> _tCoords;
			S3DVertex() {}

			S3DVertex(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, Color c, f32 tu, f32 tv)
				: _pos(x, y, z),
				_normal(nx, ny, nz),
				_color(c),
				_tCoords(tu, tv)
			{
			}

			S3DVertex(const core::vector3df& pos, const core::vector3df& normal, video::Color& color, const core::vector2d<f32>& tCoords)
			{
				_pos = pos;
				_normal = normal;
				_color = color;
				_tCoords = tCoords;
			}

			bool operator== (const S3DVertex& other) const
			{
				return (_pos == other._pos && _normal == other._normal && _color == other._color && _tCoords == other._tCoords);
			}

			bool operator != (const S3DVertex& other) const
			{
				return (_pos != other._pos || _normal != other._normal || _color != other._color || _tCoords != other._tCoords);
			}
		};
	
		struct S3DVertex2TCoords
		{
			core::vector3df _pos;
			core::vector3df _normal;
			video::Color _color;
			core::vector2d<f32> _tCoords;
			core::vector2d<f32> _tCoords2;

			S3DVertex2TCoords() {}
			S3DVertex2TCoords(f32 x, f32 y, f32 z, Color c, f32 tu, f32 tv, f32 tu2, f32 tv2)
				:_pos(x,y,z), _color(c), _tCoords(tu, tv), _tCoords2(tu2, tv2)
			{

			}
		};
	}
}