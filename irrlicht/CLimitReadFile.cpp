#include "CLimitReadFile.h"
#include "irrstring.h"
namespace irr
{
	namespace io
	{
		template<class T>
		void CLimitReadFile<T>::init()
		{
			if (!_file)
			{
				return;
			}
			_areaStart = _file->getPos();
			_areaEnd = _areaStart + _areaSize;
		}
		template<class T>
		CLimitReadFile<T>::CLimitReadFile(IReadFile* alreadyOpenedFile, size_t areaSize, const c8* name)
		{
			_areaSize = areaSize;
			_file = alreadyOpenedFile;
			_fileName = name;
			if (_file)
			{
				_file->grab();
			}
			init();
		}
		template<class T>
		CLimitReadFile<T>::~CLimitReadFile()
		{
			if (_file)
			{
				_file->drop();
			}
		}
		template<class T>
		size_t CLimitReadFile<T>::read(void * buffer, size_t sizeToRead)
		{
			size_t pos = _file->getPos();
			if ( pos >= _areaEnd)
			{
				return 0;
			}
			if ( pos + sizeToRead >= _areaEnd)
			{
				sizeToRead = _areaEnd - pos;
			}
			return _file->read(buffer, sizeToRead);
		}

		template<class T>
		bool CLimitReadFile<T>::seek(s32 finalPos, bool relativeMovement)
		{
			size_t pos = _file->getPos();
			if (relativeMovement)
			{
				if (pos + finalPos > _areaEnd)
				{
					finalPos = _areaEnd - pos;
				}
			}
			else
			{
				finalPos += _areaStart;
				if ((size_t) finalPos > _areaEnd)
				{
					return false;
				}
			}
			return _file->seek(finalPos, relativeMovement);
		}

		template<class T>
		size_t CLimitReadFile<T>::getSize()
		{
			return _areaSize;
		}

		template<class T>
		s32 CLimitReadFile<T>::getPos()
		{
			return _file->getPos() - _areaStart;
		}

		template<class T>
		const c8 * CLimitReadFile<T>::getFileName()
		{
			return _fileName.c_str();
		}
		template<class T>
		IReadFile* createLimitReadFile(const c8* fileName, IReadFile* alreadyOpenedFile, size_t areaSize)
		{
			return new CLimitReadFile<T>(alreadyOpenedFile, areaSize, fileName);
		}
		
	
	}
}