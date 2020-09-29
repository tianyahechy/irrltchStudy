#pragma once
#include "IUnknown.h"
#include "dimension2d.h"
#include "S2DVertex.h"

namespace irr
{
	namespace video
	{
		class  IZBuffer : public IUnkown
		{
		public:
			virtual ~IZBuffer() {}
			virtual void clear() = 0;
			virtual void setSize(const core::dimension2d<s32>& size) = 0;
			virtual const core::dimension2d<s32>& getSize() = 0;
			virtual TZBufferType* lock() = 0;
			virtual void unlock() = 0;

		};
		IZBuffer* createZBuffer(const core::dimension2d<s32>& size);
	}
}
