#include "CVideoNull.h"
#include "CSoftWareTexture.h"
#include "os.h"

namespace irr
{
	namespace video
	{
		ISurfaceLoader* createSurfaceloaderBMP();
		ISurfaceLoader* createSurfaceLoaderJPG();
		ISurfaceLoader* createSurfaceLoaderTGA();
		ISurfaceLoader* createSurfaceLoaderPSD();

		CVideoNull::CVideoNull(io::IFileSystem* io, const core::dimension2d<s32>& screenSize)
		{
			_screenSize = screenSize;
			_viewPort = core::rectEx<s32>(core::position2d<s32> (0,0), screenSize);
			_fileSystem = io;
			_primitiveDrawn = 0;

			if (_fileSystem)
			{
				_fileSystem->grab();
			}


			_surfaceLoader.push_back(video::createSurfaceloaderBMP());
			_surfaceLoader.push_back(video::createSurfaceLoaderJPG());
			_surfaceLoader.push_back(video::createSurfaceLoaderPSD());
			_surfaceLoader.push_back(video::createSurfaceLoaderTGA());
		}
		CVideoNull::~CVideoNull()
		{
			if (_fileSystem)
			{
				_fileSystem->drop();
			}
			deleteAllTextures();
			for (u32 i = 0; i < _surfaceLoader.size(); i++)
			{
				_surfaceLoader[i]->drop();
			}
		}
		bool CVideoNull::beginScene(bool backBuffer, bool zBuffer, Color theColor)
		{
			_primitiveDrawn = 0;
			return true;
		}
		bool CVideoNull::endScene()
		{
			_fpsCounter.registerFrame(os::Timer::getTime());
			return true;
		}
		bool CVideoNull::queryFeature(EK3D_VIDEO_DRIVER_FEATRUE feature)
		{
			return false;
		}
		void CVideoNull::setTransform(E_TRANSOFRMATION_STATE state, const core::matrix4& mat)
		{
		}
		void CVideoNull::setMaterial(const SMaterial& material)
		{
		}
		ITexture* CVideoNull::getTexture(const c8* fileName, bool generateMipLevels)
		{
			ITexture* texture = findTexture(fileName);
			if (texture)
			{
				return texture;
			}
			io::IReadFile* file = _fileSystem->createAndOpenFile(fileName);
			if (file)
			{
				texture = loadTextureFromFile(file, generateMipLevels);
				file->drop();
				if (texture)
				{
					addTexture(texture, fileName);
					texture->drop();
				}
			}
			return texture;
		}
		ITexture* CVideoNull::getTexture(io::IReadFile* file, bool generateMipLevels)
		{
			ITexture* texture = 0;
			if (file)
			{
				texture = findTexture(file->getFileName());
				if (texture)
				{
					return texture;
				}
				texture = loadTextureFromFile(file, generateMipLevels);
				if (texture)
				{
					addTexture(texture, file->getFileName());
					texture->drop();
				}
			}
			return texture;
		}
		ITexture* CVideoNull::addTexture(const core::dimension2d<s32>& size, const c8* name)
		{
			ISurface* surface = createSurface(size);
			ITexture* t = this->createDeviceDependentTexture(surface, false);
			surface->drop();
			addTexture(t, name);
			t->drop();
			return t;
		}
		void CVideoNull::setRenderTarget(video::ITexture* texture)
		{
		}
		void CVideoNull::setViewPort(const core::rectEx<s32>& area)
		{
		}
		const core::rectEx<s32>& CVideoNull::getViewPort() const
		{
			// TODO: insert return statement here
			return _viewPort;
		}
		void CVideoNull::drawIndexedTriangleList(const S3DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount)
		{
			_primitiveDrawn += triangleCount;
		}
		void CVideoNull::drawIndexedTriangleList(const S3DVertex2TCoords* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount)
		{
			_primitiveDrawn += triangleCount;
		}
		void CVideoNull::draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos)
		{
		}
		void CVideoNull::draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos, const core::rectEx<s32>& sourceRect, const core::rectEx<s32>* clipRect, Color color, bool useAlphaChannelOfTexture)
		{
		}
		void CVideoNull::draw2DRectangle(Color color, const core::rectEx<s32>& pos, const core::rectEx<s32>* clip)
		{
		}
		core::dimension2d<s32> CVideoNull::getScreenSize()
		{
			return _screenSize;
		}
		s32 CVideoNull::getFPS()
		{
			return _fpsCounter.getFPS();
		}
		u32 CVideoNull::getPrimitiveCountDrawed()
		{
			return _primitiveDrawn;
		}
		void CVideoNull::deleteAllDynamicLights()
		{
		}
		void CVideoNull::addDynamicLight(const SLight& light)
		{
		}
		s32 CVideoNull::getMaximalDynamicLightAmount()
		{
			return 0;
		}
		void CVideoNull::deleteAllTextures()
		{
			for (u32 i = 0; i <_textures.size(); i++)
			{
				_textures[i].surface->drop();
			}
			_textures.clear();
		}
		video::ITexture* CVideoNull::findTexture(const c8* fileName)
		{
			SSurface s;
			if (!fileName)
			{
				fileName = "";
			}
			s.fileName = fileName;
			s.fileName.make_lower();
			s32 index = _textures.binary_search(s);
			if (index != -1)
			{
				return _textures[index].surface;
			}
			return 0;
		}
		video::ITexture* CVideoNull::loadTextureFromFile(io::IReadFile* file, bool generateMipLevels)
		{
			ITexture* texture = 0;
			ISurface* surface = 0;

			for (u32 i = 0; i < _surfaceLoader.size(); i++)
			{
				if (_surfaceLoader[i]->isALoadableFileExtension(file->getFileName()))
				{
					surface = _surfaceLoader[i]->loadImage(file);
					if (surface)
					{
						break;
					}
				}
			}
			if (!surface)
			{
				for (int i = 0; i < _surfaceLoader.size(); i++)
				{
					if ( i != 0)
					{
						file->seek(0);
					}
					if (_surfaceLoader[i]->isALoadableFileFormat(file))
					{
						file->seek(0);
						surface = _surfaceLoader[i]->loadImage(file);
						if (surface)
						{
							break;
						}
					}
				}
			}
			if (surface)
			{
				texture = createDeviceDependentTexture(surface, generateMipLevels);
				surface->drop();
			}
			return texture;
		}
		void CVideoNull::addTexture(video::ITexture* texture, const c8* fileName)
		{
			if (!texture)
			{
				return;
			}
			if (!fileName)
			{
				fileName = "";
			}
			SSurface s;
			s.fileName = fileName;
			s.fileName.make_lower();
			s.surface = texture;
			texture->grab();
			_textures.push_back(s);
		}
		video::ITexture* CVideoNull::createDeviceDependentTexture(ISurface* surface, bool generateMipLevels)
		{
			return new CSoftwareTexture(surface);
		}

		IVideoDriver* createNullDriver(io::IFileSystem* io, const core::dimension2d<s32>& screenSize)
		{
			return new CVideoNull(io, screenSize);
		}
	}
}