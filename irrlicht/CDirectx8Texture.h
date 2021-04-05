#pragma once
#include "ITexture.h"
#include "ISurface.h"
#include <d3d9.h>

namespace irr
{
	namespace video
	{
		class CDirectX8Texture : public ITexture
		{
			CDirectX8Texture(ISurface* surface, IDirect3DDevice9* device, bool generateMipLevels);
			virtual ~CDirectX8Texture();
			virtual void* lock();
			virtual void unlock();
			virtual const core::dimension2d<s32>& getDimension();
			virtual EDriverType getDriverType();
			virtual ECOLOR_FORMAT getColorFormat();
			virtual s32 getPitch();
			IDirect3DTexture9* getDX9Texture();

		private:
			inline s32 getTextureSizeFromSurfaceSize(s32 size);
			bool copyTexture();
			ISurface* _surface;
			IDirect3DDevice9* _device;
			core::dimension2d<s32> _textureSize;
			core::dimension2d<s32> _surfaceSize;
			s32 _pitch;
			bool _surfaceHasSameSize;
		};
	}
}