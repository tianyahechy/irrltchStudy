#include "CFileSystem.h"
#include "IReadFile.h"
#include "CZipReader.h"
#include "CFileList.h"
#include <stdio.h>
#include "os.h"
#include <direct.h>

namespace irr
{
	namespace io
	{
		CFileSystem::CFileSystem()
		{
			setDebugName("CKFileSystem");
		}

		CFileSystem::~CFileSystem()
		{
			for (u32 i = 0; i < _zipFileSystems.size(); i++)
			{
				_zipFileSystems[i]->drop();
			}
		}

		IReadFile* CFileSystem::createAndOpenFile(const c8* fileName)
		{
			IReadFile* file = 0;
			for (u32 i = 0; i < _zipFileSystems.size(); i++)
			{
				file = _zipFileSystems[i]->openFile(fileName);
				if (file)
				{
					return file;
				}
			}
			file = createReadFile(fileName);
			return file;
		}
		bool CFileSystem::addZipFileArchive(const c8* fileName, bool ignoreCase, bool ignorePaths)
		{
			IReadFile* file = createReadFile(fileName);
			if (file)
			{
				CZipReader* zr = new CZipReader(file, ignoreCase, ignorePaths);
				if (zr)
				{
					_zipFileSystems.push_back(zr);
				}
				file->drop();
				return zr != 0;
			}
		}
	
		const c8* CFileSystem::getWorkingDirectory()
		{
			_getcwd(_workingDirectory, FILE_SYSTEM_MAX_PATH);
			return _workingDirectory;
		}
		
		bool CFileSystem::changeWorkingDirectoryTo(const c8* newDirectory)
		{
			return (_chdir(newDirectory) == 0);
		}

		IFileList* CFileSystem::createFileList()
		{
			return new CFileList();
		}
		
		bool CFileSystem::existFile(const c8* fileName)
		{
			for (u32 i = 0; i < _zipFileSystems.size(); i++)
			{
				if (_zipFileSystems[i]->findFile(fileName) != -1)
				{
					return true;
				}
			}
			FILE* f = fopen(fileName, "rb");
			if (f)
			{
				fclose(f);
				return true;
			}
			return false;
		}
	
		IFileSystem* createFileSystem()
		{
			return new CFileSystem();
		}
	}
}