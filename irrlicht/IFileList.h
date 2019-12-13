//ÒÑÍê³É
#pragma once
#include "IUnknown.h"

namespace irr
{
	namespace io
	{
		class IFileList : public IUnkown
		{
		public:
			virtual ~IFileList() {}
			virtual s32 getFileCount() = 0;
			virtual const c8* getFileName(s32 index) = 0;
			virtual bool isDirectory(s32 index) = 0;
		};
	}
}