#include "CSoftWareTexture.h"
#include "os.h"
namespace irr
{
	namespace video
	{
		CSoftwareTexture::CSoftwareTexture(ISurface* surface)
		{
			_surface = surface;
			_texture = 0;
			if (_surface)
			{
				_surface->grab();
				core::dimension2d<s32> origSize = _surface->getDimension();
				core::dimension2d<s32> optSize;
				optSize._width = this->getTextureSizeFromSurfaceSize(origSize._width);
				optSize._height = this->getTextureSizeFromSurfaceSize(origSize._height);

				if (optSize != origSize)
				{
					_texture = createSurface(optSize);
					_surface->copyTo(_texture);
				}
				else
				{
					_texture = _surface;
					_texture->grab();
				}

			}
		}
	
		CSoftwareTexture::~CSoftwareTexture()
		{
			if (_surface)
			{
				_surface->drop();
			}
			if (_texture)
			{
				_texture->drop();
			}
		}
		void* CSoftwareTexture::lock()
		{
			return _surface->lock();
		}
		void CSoftwareTexture::unlock()
		{
			if (_surface != _texture)
			{
				_surface->copyToScaling(_texture);
			}
		}
		const core::dimension2d<s32>& CSoftwareTexture::getDimension()
		{
			// TODO: insert return statement here
			return _surface->getDimension();
		}
		ISurface* CSoftwareTexture::getSurface()
		{
			return _surface;
		}
		ISurface* CSoftwareTexture::getTexture()
		{
			return _texture;
		}
		EDriverType CSoftwareTexture::getDriverType()
		{
			return DT_SOFTWARE;
		}
		ECOLOR_FORMAT CSoftwareTexture::getColorFormat()
		{
			return EHCF_R5G5B5;
		}
		s32 CSoftwareTexture::getPitch()
		{
			return _surface->getDimension()._width * 2;
		}
		inline s32 CSoftwareTexture::getTextureSizeFromSurfaceSize(s32 size)
		{
			s32 ts = 0x01;
			while (ts < size)
			{
				ts <<= 1;
			}
			return ts;
		}
	}
}