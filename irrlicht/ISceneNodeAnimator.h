#pragma once
#include "IUnknown.h"
#include "vector3d.h"
namespace irr
{
	namespace scene
	{
		class ISceneNode;
		class ISceneNodeAnimator : public IUnkown
		{
		public:
			virtual ~ISceneNodeAnimator() {}
			virtual void animateNode(ISceneNode* node, u32 timeMs) = 0;
		};
	}
}
