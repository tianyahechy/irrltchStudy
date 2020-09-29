#pragma once
#include "vector2d.h"
typedef signed short TZBufferType;

namespace irr
{
	namespace video
	{
		struct S2DVertex
		{
			core::vector2d<s32> Pos;
			core::vector2d<s32> TCoords;
			TZBufferType		ZValue;
			s16					Color;
		};
	}
}