//рямЙЁи
#include "CReadFile.h"
#include <stdio.h>
namespace irr
{
	namespace io
	{
		CReadFile::CReadFile(const c8* fileName)
		{
			_fileSize = 0;
			_fileName = fileName;
		}
		CReadFile::~CReadFile()
		{
			if (_file)
			{
				fclose(_file);
			}
		}
		inline bool CReadFile::isOpen()
		{
			return _file != 0;
		}
		size_t CReadFile::read(void* buffer, size_t sizeToRead)
		{
			if (!isOpen())
			{
				return 0;
			}
			return fread(buffer, 1, sizeToRead, _file);
		}
		bool CReadFile::seek(s32 finalPos, bool relativeMovement)
		{
			if (!isOpen())
			{
				return false;
			}
			return fseek(_file, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET) == 0;
		}
		size_t CReadFile::getSize()
		{
			return _fileSize;
		}
		s32 CReadFile::getPos()
		{
			return ftell(_file);
		}
		void CReadFile::openFile()
		{
			_file = fopen(_fileName.c_str(), "rb");
			if (_file)
			{
				fseek(_file, 0, SEEK_END);
				_fileSize = ftell(_file);
				fseek(_file, 0, SEEK_SET);
			}
		}
		
		const c8* CReadFile::getFileName()
		{
			return _fileName.c_str();
		}
		IReadFile* createReadFile(const c8* fileName)
		{
			CReadFile* file = new CReadFile(fileName);
			if (file->isOpen())
			{
				return file;
			}
			file->drop();
			return 0;
		}
	}
}