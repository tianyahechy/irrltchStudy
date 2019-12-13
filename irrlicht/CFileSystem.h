#pragma once
#include "IFileSystem.h"
#include "array.h"

namespace irr
{
	namespace io
	{
		class CZipReader;
		const s32 FILE_SYSTEM_MAX_PATH = 1024;

		class CFileSystem : public IFileSystem
		{
		private:
			core::array<CZipReader*> _zipFileSystems;
			c8 _workingDirectory[FILE_SYSTEM_MAX_PATH];

		public:
			CFileSystem();
			virtual ~CFileSystem();
			virtual IReadFile* createAndOpenFile(const c8* fileName);
			virtual bool addZipFileArchive(const c8* fileName, bool ignoreCase = true, bool ignorePaths = true);
			virtual const c8* getWorkingDirectory();
			virtual bool changeWorkingDirectoryTo(const c8* newDirectory);
			virtual IFileList * createFileList();
			virtual bool existFile(const c8* fileName);

		};
	}
}