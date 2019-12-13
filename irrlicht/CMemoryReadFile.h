#pragma once
#include "IReadFile.h"
#include "irrstring.h"

namespace irr
{
	namespace io
	{
		template<class T>
		class CMemoryReadFile : public IReadFile
		{
		private:
			core::string _fileName;
			void* _buffer;
			u32 _len;
			u32 _pos;
			bool _deleteMemoryWhenDropped;

		public:
			CMemoryReadFile(void * memory, s32 len, const c8* fileName, bool deleteMemoryWhenDropped);
			virtual ~CMemoryReadFile();
			virtual size_t read(void * buffer, size_t sizeToRead);
			virtual bool seek(s32 finalPos, bool relativeMovement = false);
			virtual size_t getSize();
			virtual s32 getPos();
			virtual const c8* getFileName();
		};
	
	}
}
