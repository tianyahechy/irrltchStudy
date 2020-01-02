#pragma once
#include "IMesh.h"
#include "ISceneNode.h"

namespace irr
{
	namespace scene
	{
		class IBspTreeSceneNode : public ISceneNode
		{
			IBspTreeSceneNode(ISceneNode* parent, ISceneManager * mgr, s32 id)
				: ISceneNode( parent, mgr, id, core::vector3df(0, 0, 0 ), core::vector3df(0, 0, 0), core::vector3df(1.0f, 1.0f, 1.0f ))
			{

			}
			virtual ~IBspTreeSceneNode() {}
		};
	}
}