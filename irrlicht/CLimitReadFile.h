#pragma once
#include "IReadFile.h"
#include "irrstring.h"

namespace irr
{
	class CUnicodeConverter;
	namespace io
	{
		template<class T>
		class CLimitReadFile : public IReadFile
		{
		private:
			void init();
			core::string _fileName;
			size_t _areaSize;
			size_t _areaStart;
			size_t _areaEnd;
			IReadFile* _file;

		public:
			CLimitReadFile(IReadFile* alreadyOpenedFile, size_t areaSize, const c8* name);
			virtual ~CLimitReadFile();
			virtual size_t read(void * buffer, size_t sizeToRead);
			virtual bool seek(s32 finalPos, bool relativeMovement = false);
			virtual size_t getSize();
			virtual s32 getPos();
			virtual const c8* getFileName();
		};
	}
}
