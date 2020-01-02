#pragma once

#include "ISceneNode.h"
namespace irr
{
	namespace scene
	{
		class IBillboardSceneNode : public ISceneNode
		{
		public:
			IBillboardSceneNode(ISceneNode * parent, ISceneManager* mgr, s32 id, const core::vector3df& position = core::vector3df(0, 0, 0))
				:ISceneNode( parent, mgr, id, position)
			{

			}
			virtual void setSize(const core::dimension2d<f32>& size) = 0;
			virtual const core::dimension2d<f32>& getSize() = 0;
		};
	}
}