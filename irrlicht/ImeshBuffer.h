#pragma once
#include "IUnknown.h"
#include "SMaterial.h"
#include "array.h"
#include "aabbox3d.h"
#include "S3DVertex.h"

namespace irr
{
	namespace scene
	{
		class IMeshBuffer : public IUnkown
		{
		public:
			virtual ~IMeshBuffer() {}
			virtual video::SMaterial& getMaterial() = 0;
			virtual const video::SMaterial& getMaterial() const= 0;
			virtual video::E_VERTEX_TYPE getVertexType() const = 0;
			virtual const void* getVertices() const = 0;
			virtual void* getVertices() = 0;
			virtual s32 getVertexCount() const = 0;
			virtual const u16* getIndices() const = 0;
			virtual s32 getIndexCount() = 0;
			virtual const core::aabbox3d<f32>& getBoundingBox() const = 0;
		};
	}
}