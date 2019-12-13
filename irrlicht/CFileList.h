#pragma once
#include "IFileList.h"
#include "irrstring.h"
#include "array.h"

namespace irr
{
	namespace io
	{
		class CFileList : public IFileList
		{
		public:
			CFileList();
			virtual ~CFileList();
			//返回文件列表中的文件数
			virtual s32 getFileCount();
			//返回文件列表中给定索引的文件名
			virtual const c8* getFileName( s32 index);
			//返回文件是否一个文件夹
			virtual bool isDirectory(s32 index);

		private:
			struct FileEntry
			{
				irr::core::string _name;
				s32 _Size;
				bool _isDirectory;
			};
			core::array<FileEntry> _files;

		};
	}
}