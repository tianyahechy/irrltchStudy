#pragma once
#include "IZBuffer.h"

namespace irr
{
	namespace video
	{
		class  CZBuffer : public IZBuffer
		{
		public:
			CZBuffer(const core::dimension2d<s32>& size);
			virtual ~CZBuffer();
			virtual void clear();
			virtual void setSize(const core::dimension2d<s32>& size);
			virtual const core::dimension2d<s32>& getSize();
			virtual TZBufferType* lock();
			virtual void unlock();

		private:
			TZBufferType*	_buffer;
			TZBufferType*	_bufferEnd;
			core::dimension2d<s32>	_size;
			s32				_totalSize;
		};
	}
}
