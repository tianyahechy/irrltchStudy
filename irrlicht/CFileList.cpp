#include "CFileList.h"
#include <stdio.h>
#include <io.h>

namespace irr
{
	namespace io
	{
		CFileList::CFileList()
		{
			struct _finddata_t c_file;
			s32 hFile;
			FileEntry entry;
			if ((hFile = _findfirst("*", &c_file) ) != -1L)
			{
				do
				{
					entry._name = c_file.name;
					entry._Size = c_file.size;
					entry._isDirectory = (_A_SUBDIR & c_file.attrib) != 0;
					_files.push_back(entry);
				} while ( _findnext(hFile,&c_file)== 0);
				_findclose(hFile);
			}
		}
		CFileList::~CFileList()
		{
		}
		s32 CFileList::getFileCount()
		{
			return _files.size();
		}
		const c8* CFileList::getFileName(s32 index)
		{
			if (index < 0 || index > (s32) _files.size())
			{
				return 0;
			}
			return _files[index]._name.c_str();
		}
		
		bool CFileList::isDirectory(s32 index)
		{
			if (index < 0 || index >(s32) _files.size())
			{
				return 0;
			}
			return _files[index]._isDirectory;

		}
	
	}
}


