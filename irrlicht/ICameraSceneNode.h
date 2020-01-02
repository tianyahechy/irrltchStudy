#pragma once
#include "ISceneNode.h"
#include "IEventReceiver.h"
namespace irr
{
	namespace scene
	{
		struct SViewFrustum
		{
			enum planes
			{
				CVA_FAR_PLANE = 0,
				CVA_NEAR_PLANE,
				CVA_LEFT_PLANE,
				CVA_RIGHT_PLANE,
				CVA_BOTTOM_PLANE,
				CVA_TOP_PLANE,
				CVA_PLANE_COUNT
			};
			core::plane3dex<f32> planes[CVA_PLANE_COUNT];
			core::vector3df rightFarDown;
			core::vector3df leftFarDown;
			core::vector3df rightFarUp;
			core::vector3df leftFarUp;

			core::aabbox3d<f32> box;
		};
		
		class ICameraSceneNode : public ISceneNode, public IEventReceiver
		{
			ICameraSceneNode(ISceneNode* parent, ISceneManager * mgr, s32 id,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f))
				:ISceneNode(parent, mgr, id, position, rotation, scale)
			{
			}
			virtual~ ICameraSceneNode() {}
			virtual void setProjectionMatrix(const core::matrix4& projection) = 0;
			virtual const core::matrix4& getProjectionMatrix() = 0;
			virtual const core::matrix4& getViewMatrix() = 0;
			virtual bool OnEvent(SEvent event) = 0;
			virtual void setTarget(const core::vector3df& pos) = 0;
			virtual core::vector3df getTarget() const = 0;
			virtual void setUpVector(const core::vector3df& pos) = 0;
			virtual core::vector3df getUpVector() const = 0;
			virtual f32 getNearValue() = 0;
			virtual f32 getFarValue() = 0;
			virtual f32 getAspectRatio() = 0;
			virtual f32 getFOV() = 0;
			virtual void setNearValue(f32 zn) = 0;
			virtual void setFarValue(f32 zf) = 0;
			virtual void setAspectRatio(f32 aspect) = 0;
			virtual void setFOV(f32 fovy) = 0;
			virtual const SViewFrustum* getViewFrustum() = 0;

		};
	
	}
}