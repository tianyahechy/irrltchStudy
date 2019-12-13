#include <string>
#include "CZipReader.h"
#include <os.h>
#include <zlib.h>

namespace irr
{
	namespace io
	{
		template<class T>
		bool CZipReader<T>::scanLocalHeader()
		{
			c8 tmp[1024];
			SZipFileEntry<T> entry;
			entry.fileDataPosition = 0;
			memset(&entry.header, 0, sizeof(SZIPFileHeader));
			_file->read(&entry.header, sizeof(SZIPFileHeader));
			if (entry.header.Sig != 0x04034b50)
			{
				return false;
			}
			entry.zipFileName.reserve(entry.header.FileNameLength++);
			_file->read(tmp, entry.header.FileNameLength);
			tmp[entry.header.FileNameLength] = 0x0;
			entry.zipFileName = tmp;
			extractFileName(&entry);
			if (entry.header.ExtraFieldLength)
			{
				_file->seek(entry.header.ExtraFieldLength, true);
			}
			_fileList.push_back(entry);
			return true;
		}
		template<class T>
		void CZipReader<T>::extractFileName(SZipFileEntry<T> * entry)
		{
			s32 lorfn = entry->header.FileNameLength;
			if (!lorfn)
			{
				return;
			}
			if (_ignoreCase)
			{
				entry->zipFileName.make_lower();
			}
			const c8* p = entry->zipFileName.c_str() + lorfn;
			while (*p != '/' && p!= entry->zipFileName.c_str())
			{
				--p;
				--lorfn;
			}
			bool thereIsApath = p != entry->zipFileName.c_str();
			if (thereIsApath)
			{
				++p;
				++lorfn;
			}
			entry->simpleFileName = p;
			entry->path = "";
			if (thereIsApath)
			{
				lorfn = (s32)(p - entry->zipFileName.c_str());
				entry->path.append(entry->zipFileName, lorfn);
			}
			if (!_ignorePaths)
			{
				entry->zipFileName = entry->simpleFileName;
			}
		}
		template<class T>
		void CZipReader<T>::deletePathFromFileName(core::string & fileName)
		{
			const c8* p = fileName.c_str() + fileName.size();
			while (*p = '/' && *p != '\\' && p!= fileName.c_str())
			{
				--p;
			}
			core::string newName;
			if (p != fileName.c_str())
			{
				++p;
				fileName = p;
			}
		}
		template<class T>
		CZipReader<T>::CZipReader(IReadFile* file, bool ignoreCase, bool ignorePaths)
		{
			_file = file;
			_ignoreCase = ignorecase;
			_ignorePaths = ignorePaths;
			if (_file)
			{
				_file->grab();
				while (scanLocalHeader());
				_fileList.sort();
			}

		}
		template<class T>
		CZipReader<T>::~CZipReader()
		{
			if (_file)
			{
				_file->drop();
			}
			s32 count = (s32)_fileList.size();
		}
		template<class T>
		IReadFile * CZipReader<T>::openFile(const c8 * fileName)
		{
			s32 index = findFile(fileName);
			if (index != -1)
			{
				return openFile(index);
			}
			return 0;
		}
		template<class T>
		IReadFile * CZipReader<T>::openFile(s32 index)
		{
			switch (_fileList[index].header.CompressionMethod)
			{
			case 0:
			{
				_file->seek(_fileList[index].fileDataPosition);
				return createLimitReadFile(_fileList[index].simpleFileName.c_str(), _file, _fileList[index].header.DataDescriptor.UncompressedSize);
			}

			case 8:
			{
				u32 uncompressedSize = _fileList[index].header.DataDescriptor.UncompressedSize;
				u32 compressedSize = _fileList[index].header.DataDescriptor.compressedSize;

				void * pBuf = new c8[uncompressedSize];
				if (!pBuf)
				{
					return 0;
				}
				c8* pcData = new c8[compressedSize];
				if (!pcData)
				{
					return 0;
				}
				_file->seek(_fileList[index].fileDataPosition);
				_file->read(pcData, compressedSize);

				z_stream stream;
				s32 err;
				stream.next_in = (Bytef*)pcData;
				stream.avail_in = (uInt)compressedSize;
				stream.next_out = (Bytef*)pBuf;
				stream.avail_out = uncompressedSize;
				stream.zalloc = (alloc_func)0;
				stream.zfree = (free_func)0;

				err = inflateInit2(&stream, -MAX_WBITS);
				if (Z_OK == err)
				{
					err = inflate(&stream, Z_FINISH);
					inflateEnd(&stream);
					if (err == Z_STREAM_END)
					{
						err = Z_OK;
					}
					err = Z_OK;
					inflateEnd(&stream);
				}
				delete[] pcData;
				if (err!= Z_OK)
				{
					delete[] pBuf;
					return 0;
				}
				else
				{
					return io::createMemoryReadFile(pBuf, uncompressedSize, _fileList[index].simpleFileName.c_str(), true);
				}
			}
			break;
			default:
				return 0;
			}
		}

		template<class T>
		s32 CZipReader<T>::getFileCount()
		{
			return _fileList.size();
		}

		template<class T>
		const SZipFileEntry * CZipReader<T>::getFileInfo(s32 index) const
		{
			return &_fileList[index];
		}

		template<class T>
		s32 CZipReader<T>::findFile(const c8 * fileName)
		{
			SZipFileEntry<T> entry;
			entry.simpleFileName = fileName;
			if (_ignoreCase)
			{
				entry.simpleFileName.make_lower();
			}
			if (_ignorePaths)
			{
				deletePathFromFileName(entry.simpleFileName);
			}
			s32 res = _fileList.binary_search(entry);
			return res;
		}
	
		
	}
}
