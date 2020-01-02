#pragma once

#include "ISceneNode.h"
#include "slight.h"
namespace irr
{
	namespace scene
	{
		class ILightSceneNode : public ISceneNode
		{
			ILightSceneNode(ISceneNode * parent, ISceneManager * mgr, s32 id,
				const core::vector3df& position = core::vector3df(0, 0, 0))
				:ISceneNode(parent, mgr, id, position)
			{

			}
			virtual video::SLight& getLightData() = 0;
		};
	}
}
