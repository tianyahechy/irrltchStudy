//ÒÑÍê³É

#pragma once
#include "IUnknown.h"

namespace irr
{
	namespace io
	{
		class IReadFile : public IUnkown
		{
		public:
			virtual ~IReadFile() {}
			virtual size_t read(void* buffer, size_t sizeToRead) = 0;
			virtual bool seek(s32 finalPos, bool relativeMovement = false) = 0;
			virtual size_t getSize() = 0;
			virtual s32 getPos() = 0;
			virtual const c8* getFileName() = 0;
		};
		IReadFile * createReadFile(const c8 * fileName);
		IReadFile * createLimitReadFile(const c8 * fileName, IReadFile* alreadyOpenedFile, size_t areaSize);
		IReadFile* createMemoryReadFile(void * memory, s32 size, const c8 * fileName, bool deleteMemoryWhenDropped);
	}
}

