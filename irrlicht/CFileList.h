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
			//�����ļ��б��е��ļ���
			virtual s32 getFileCount();
			//�����ļ��б��и����������ļ���
			virtual const c8* getFileName( s32 index);
			//�����ļ��Ƿ�һ���ļ���
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