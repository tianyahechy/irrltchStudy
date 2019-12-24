#pragma once
#include "IUnknown.h"
#include "ImeshBuffer.h"
namespace irr
{
	namespace scene
	{
		class IMesh : public IUnkown
		{
		public:
			virtual ~IMesh() {}
			virtual s32 getMeshBufferCount() = 0;
			virtual IMeshBuffer* getMeshBuffer(s32 nr) = 0;
			virtual const core::aabbox3d<f32>& getBoundingBox() const = 0;
			virtual void setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newValue) = 0;
		};
	}
}