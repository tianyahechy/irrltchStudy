#include "CMemoryReadFile.h"
#include <memory.h>

namespace irr
{
	namespace io
	{
		template<class T>
		CMemoryReadFile<T>::CMemoryReadFile(void * memory, s32 len, const c8 * fileName, bool deleteMemoryWhenDropped)
		{
			_buffer = memory;
			_len = len;
			_pos = 0;
			_deleteMemoryWhenDropped = deleteMemoryWhenDropped;
			_fileName = fileName;
		}

		template<class T>
		CMemoryReadFile<T>::~CMemoryReadFile()
		{
			if (_deleteMemoryWhenDropped)
			{
				delete[] _buffer;
			}
		}

		template<class T>
		size_t CMemoryReadFile<T>::read(void * buffer, size_t sizeToRead)
		{
			size_t amount = sizeToRead;
			if (_pos + amount > _len)
			{
				amount -= _pos + amount - _len;
			}
			if (amount < 0)
			{
				amount = 0;
			}
			c8* p = (c8*)_buffer;
			memcpy(buffer, p + _pos, amount);

			_pos += static_cast<u32> (amount);
			return amount;
		}

		template<class T>
		bool CMemoryReadFile<T>::seek(s32 finalPos, bool relativeMovement)
		{
			if (relativeMovement)
			{
				if (_pos + finalPos > _len)
				{
					return false;
				}
				_pos += finalPos;
			}
			else
			{
				if ((unsigned) finalPos > _len)
				{
					return false;
				}
				_pos = finalPos;
			}
			return true;
		}

		template<class T>
		size_t CMemoryReadFile<T>::getSize()
		{
			return _len;
		}

		template<class T>
		s32 CMemoryReadFile<T>::getPos()
		{
			return _pos;
		}

		template<class T>
		const c8 * CMemoryReadFile<T>::getFileName()
		{
			return _fileName.c_str();
		}
		template<class T>
		IReadFile* createMemoryReadFile(void* memory, s32 size, const c8* fileName, bool deleteMemoryWhenDropped)
		{
			CMemoryReadFile<T>* file = new CMemoryReadFile(memory, size, fileName, deleteMemoryWhenDropped);
			return file;
		}

	}
}