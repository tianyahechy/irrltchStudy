#pragma once
#include "IUnknown.h"
#include "vector3d.h"
#include "dimension2d.h"
#include "color.h"

namespace irr
{
	namespace io
	{
		class IFileSystem;
	}
	namespace video
	{
		class IVideoDriver;
	}
	
	namespace scene
	{
		enum ESceneNodeRenderTime
		{
			SNRT_LIGHT_AND_CAMERA,
			SNRT_DEFAULT,
			SNRT_SHADOW,
			SNRT_COUNT
		};
		class IMesh;
		class IAnimatedMesh;
		class ISceneNode;
		class ICameraSceneNode;
		class IAnimatedMeshSceneNode;
		class IBspTreeSceneNode;
		class ISceneNodeAnimator;
		class ILightSceneNode;
		class IBillboardSceneNode;

		class ISceneManager : public IUnkown
		{
		public:
			virtual ~ISceneManager() {}
			virtual IAnimatedMesh* getMesh(const c8 * fileName) = 0;
			virtual video::IVideoDriver* getVideoDriver() = 0;
			virtual ISceneNode* addTestSceneNode(f32 size = 10.0f, ISceneNode* parent = 0, s32 id = -1,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)) = 0;

			virtual IAnimatedMeshSceneNode* addAnimatedMeshSceneNode(IAnimatedMesh* mesh, ISceneNode* parent = 0, s32 id = -1,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)) = 0;

			virtual ISceneNode* addMeshSceneNode(IMesh* mesh, ISceneNode* parent = 0, s32 id = -1,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& rotation = core::vector3df(0, 0, 0),
				const core::vector3df	 = core::vector3df(1.0f, 1.0f, 1.0f)) = 0;

			virtual IBspTreeSceneNode* addBspTreeSceneNode(IMesh* mesh, ISceneNode* parent = 0, s32 id = -1) = 0;
			virtual ISceneNode* addOctTreeSceneNode(IMesh* mesh, ISceneNode* parent = 0, s32 id = -1) = 0;
			virtual ICameraSceneNode* addCameraSceneNode(ISceneNode* parent = 0,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				const core::vector3df& lookat = core::vector3df(0, 0, 100),
				s32 id = -1 ) = 0;
			virtual ICameraSceneNode* addCameraSceneNodeMaya(
				ISceneNode* parent = 0,
				f32 rotateSpeed = -1500.0f,
				f32 zoomSpeed = 200.0f,
				f32 translationSpeed = 1500.0f,
				s32 id = -1
			) = 0;

			virtual ILightSceneNode* addLightSceneNode(ISceneNode* parent = 0,
				const core::vector3df& position = core::vector3df(0, 0, 0),
				video::Colorf color = video::Colorf(1.0f, 1.0f, 1.0f), f32 range = 100.0f, s32 id = -1) = 0;

			virtual ILightSceneNode* addBillboardSceneNode(ISceneNode* parent = 0,
				const core::dimension2d<f32>& size = core::dimension2d<f32>(10.0f, 10.0f),
				const core::vector3df& position = core::vector3df(0, 0, 0),
				s32 id = -1) = 0;

			virtual ICameraSceneNode* getActiveCamera() = 0;

			virtual void setActiveCamera(ICameraSceneNode* camera) = 0;

			virtual void registerNodeForRendering(ISceneNode* node, ESceneNodeRenderTime time = SNRT_DEFAULT) = 0;

			virtual void drawAll() = 0;

			virtual ISceneNodeAnimator* createRotationAnimator(const core::vector3df& rotationPerSecond) = 0;

			virtual ISceneNodeAnimator* createFlyCircleAnimator(const core::vector3df& normal, f32 radius, f32 speed = 0.001f) = 0;

		};
		ISceneManager * createSceneManager(video::IVideoDriver* driver, io::IFileSystem* fs);
	}
}