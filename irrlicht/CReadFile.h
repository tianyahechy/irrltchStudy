#pragma once
#include <stdio.h>
#include "IReadFile.h"
#include "irrstring.h"

namespace irr
{
	namespace io
	{
		class CReadFile : public IReadFile
		{
		private:
			core::string _filename;
			FILE* _file;
			size_t _fileSize;

			void openFile();

		public:
			CReadFile(const wchar_t* fileName);
			CReadFile(const c8* fileName);
			virtual ~CReadFile();

			virtual size_t read(void* buffer, size_t sizeToRead);
			virtual bool seek(s32 finalPos, bool relativeMovement = false);
			virtual size_t getSize();
			bool isOpen();
			virtual s32 getPos();
			virtual const c8* getFileName();
		};
	}
}