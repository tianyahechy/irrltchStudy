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
		class IAnimation;
		class ISceneNode;
		class ICameraSceneNode;
		class IAnimatedMeshSceneNode;
		class IBspTreeSceneNode;
		class ISceneNodeAnimator;
		class ILightSceneNode;
		class IBillboardSceneNode;
	}
}