#pragma once

#include "IUnknown.h"
#include "IReadFile.h"
#include "ISurface.h"

namespace irr
{
	namespace video
	{
		class ISurfaceLoader : public IUnkown
		{
		public:
			virtual ~ISurfaceLoader()
			{
			}
			virtual bool isALoadableFileExtension(const c8* fileName) = 0;
			virtual bool isALoadableFileFormat(irr::io::IReadFile* file) = 0;
			virtual ISurface* loadImage(irr::io::IReadFile* file) = 0;
		};
	}
}
