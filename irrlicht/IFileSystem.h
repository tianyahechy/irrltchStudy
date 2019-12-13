//ÒÑÍê³É

#pragma once
#include "IUnknown.h"

namespace irr
{
	namespace io
	{
		class IReadFile;
		class IFileList;

		class IFileSystem : public IUnkown
		{
		public:
			virtual ~IFileSystem() {}
			virtual IReadFile * createAndOpenFile(const c8* fileName) = 0;
			virtual bool addZipFileArchive(const c8* fileName, bool ignoreCase = true, bool ignorePaths = true) = 0;
			virtual const c8* getWorkingDirectory() = 0;
			virtual bool changeWorkingDirectoryTo(const c8* newDirectory) = 0;
			virtual IFileList* createFileList() = 0;
			virtual bool existFile(const c8* fileName) = 0;
		};

	}
}