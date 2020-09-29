#include "CZBuffer.h"
namespace irr
{
	namespace video
	{
		CZBuffer::CZBuffer(const core::dimension2d<s32>& size)
		{
			_buffer = 0;
			_size = core::dimension2d<s32>(0, 0);
			_totalSize = 0;
			_bufferEnd = 0;
			setSize(size);
		}
		CZBuffer::~CZBuffer()
		{
			if (_buffer)
			{
				delete[] _buffer;
			}
		}
		void CZBuffer::clear()
		{
			TZBufferType* p = _buffer;
			while (p != _bufferEnd)
			{
				*p = 0;
				++p;

			}
		}
		void CZBuffer::setSize(const core::dimension2d<s32>& size)
		{
			if (_size == size)
			{
				return;
			}
			_size = size;
			if (_buffer)
			{
				delete[] _buffer;
			}
			_totalSize = size._width * size._height;
			_buffer = new TZBufferType[_totalSize];
			_bufferEnd = _buffer + _totalSize;
		}
		const core::dimension2d<s32>& CZBuffer::getSize()
		{
			// TODO: insert return statement here
			return _size;
		}
		TZBufferType* CZBuffer::lock()
		{
			return _buffer;
		}
		void CZBuffer::unlock()
		{
		}
		IZBuffer* createZBuffer(const core::dimension2d<s32>& size)
		{
			return new CZBuffer(size);
		}
	}
}