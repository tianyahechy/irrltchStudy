#pragma once
#include "IVideoDriver.h"
#include "IFileSystem.h"
#include "ISurfacePresenter.h"
#include "array.h"
#include "irrstring.h"
#include "ISurfaceLoader.h"
#include "CFPSCounter.h"
#include "S3DVertex.h"

namespace irr
{
	namespace video
	{
		class CVideoNull : public IVideoDriver
		{
			CVideoNull(io::IFileSystem* io, const core::dimension2d<s32>& screenSize);
			virtual ~CVideoNull();
			virtual bool beginScene(bool backBuffer, bool zBuffer, Color theColor);
			virtual bool endScene();			
			virtual bool queryFeature(EK3D_VIDEO_DRIVER_FEATRUE feature) ;
			virtual void setTransform(E_TRANSOFRMATION_STATE state, const core::matrix4& mat) ;
			virtual void setMaterial(const SMaterial& material) ;
			virtual ITexture* getTexture(const c8* fileName, bool generateMipLevels = false) ;
			virtual ITexture* getTexture(io::IReadFile* file, bool generateMipLevels = false) ;
			virtual ITexture* addTexture(const core::dimension2d<s32>& size, const c8* name) ;
			virtual void setRenderTarget(video::ITexture* texture) ;
			virtual void setViewPort(const core::rectEx<s32>& area) ;
			virtual const core::rectEx<s32>& getViewPort() const ;
			virtual void drawIndexedTriangleList(const S3DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount) ;
			virtual void drawIndexedTriangleList(const S3DVertex2TCoords* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount) ;
			virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos) ;
			virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos,
				const core::rectEx<s32>& sourceRect, const core::rectEx<s32>* clipRect ,
				Color color = Color(255, 255, 255, 255), bool useAlphaChannelOfTexture = false) ;
			virtual void draw2DRectangle(Color color, const core::rectEx<s32>& pos, const core::rectEx<s32>* clip ) ;
			virtual core::dimension2d<s32> getScreenSize() ;
			virtual s32 getFPS() ;
			virtual u32 getPrimitiveCountDrawed() ;
			virtual void deleteAllDynamicLights() ;
			virtual void addDynamicLight(const SLight& light) ;
			virtual s32 getMaximalDynamicLightAmount() ;

		protected:
			void deleteAllTextures();
			video::ITexture* findTexture(const c8* fileName);
			video::ITexture* loadTextureFromFile(io::IReadFile* file, bool generateMipLevels);
			void addTexture(video::ITexture* surface, const c8* fileName);
			virtual video::ITexture* createDeviceDependentTexture(ISurface* surface, bool generateMipLevels);

			struct SSurface
			{
				irr::core::string fileName;
				video::ITexture* surface;
				bool operator< (const SSurface& other) const
				{
					return fileName < other.fileName;
				}

			};

			core::array<SSurface> _textures;
			core::array<video::ISurfaceLoader*> _surfaceLoader;
			io::IFileSystem* _fileSystem;
			core::rectEx<s32> _viewPort;
			core::dimension2d<s32> _screenSize;
			CFPSCounter _fpsCounter;
			u32 _primitiveDrawn;
		};
	}
}