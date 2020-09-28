#pragma once
#include "ITexture.h"
#include "ISurface.h"

namespace irr
{
	namespace video
	{
		class CSoftwareTexture : public ITexture
		{
		public:
			CSoftwareTexture(ISurface* surface);
			virtual ~CSoftwareTexture();
			virtual void* lock() ;
			virtual void unlock() ;
			virtual const core::dimension2d<s32>& getDimension() ;
			virtual ISurface* getSurface();
			virtual ISurface* getTexture();
			virtual EDriverType getDriverType();
			virtual ECOLOR_FORMAT getColorFormat();
			virtual s32 getPitch();
			
		private:
			inline s32 getTextureSizeFromSurfaceSize(s32 size);
			ISurface* _surface;
			ISurface* _texture;
		};
	}
}