#pragma once
#include "ISceneNode.h"
namespace irr
{
	namespace scene
	{
		class IAnimatedMeshSceneNode : public ISceneNode
		{
		public:
			IAnimatedMeshSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f))
				:ISceneNode( parent, mgr, id, position, rotation, scale)
			{

			}
			virtual ~IAnimatedMeshSceneNode() {}
			virtual void setCurrentFrame(s32 frame) = 0;
			virtual bool setFrameLoop(s32 begin, s32 end) = 0;
			virtual void setAnimationSpeed(s32 framesPerSecond) = 0;
		};
	}
}