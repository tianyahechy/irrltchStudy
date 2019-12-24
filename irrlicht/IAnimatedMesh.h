#pragma once
#include "IUnknown.h"
#include "IMesh.h"

namespace irr
{
	namespace scene
	{
		class IAnimatedMesh : public IUnkown
		{
		public:
			virtual ~IAnimatedMesh() {}
			virtual s32 getFrameCount() = 0;
			virtual IMesh* getMesh(s32 frame, s32 detialLevel = 255) = 0;
		};
	}
}
