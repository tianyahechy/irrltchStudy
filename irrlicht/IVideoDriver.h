#pragma once
#include "rect.h"
#include "color.h"
#include "ITexture.h"
#include "matrix4.h"
#include "dimension2d.h"
#include "position2d.h"
#include "IReadFile.h"
#include "SMaterial.h"
#include "slight.h"

namespace irr
{
	namespace video
	{
		struct S3DVertex;
		struct S3DVertex2TCoords;
		enum EK3D_VIDEO_DRIVER_FEATRUE
		{
			EK3DVDF_RENDER_TO_TARGET = 0,
			EK3DVDF_BILINEAR_FILER,
			EK3DVDF_HARDWARE_TL,
			EK3DVDF_MIP_MAP,
		};
		enum E_TRANSOFRMATION_STATE
		{
			TS_VIEW = 0,
			TS_WORLD,
			TS_PROJECTION,
			TS_COUNT
		};
		
		class IVideoDriver : public IUnkown
		{
		public:
			virtual ~IVideoDriver() {}
			virtual bool beginScene(bool backBuffer, bool zBuffer, Color color) = 0;
			virtual bool endScene() = 0;
			virtual bool queryFeature(EK3D_VIDEO_DRIVER_FEATRUE feature) = 0;
			virtual void setTransform(E_TRANSOFRMATION_STATE state, const core::matrix4& mat) = 0;
			virtual void setMaterial(const SMaterial& material) = 0;
			virtual ITexture* getTexture(const c8* fileName, bool generateMipLevels = false) = 0;
			virtual ITexture* getTexture(io::IReadFile* file, bool generateMipLevels = false) = 0;
			virtual ITexture* addTexture(const core::dimension2d<s32>& size, const c8* name) = 0;
			virtual void setRenderTarget(video::ITexture* texture) = 0;
			virtual void setViewPort(const core::rectEx<s32>& area) = 0;
			virtual const core::rectEx<s32>& getViewPort() const = 0;
			virtual void drawIndexedTriangleList(const S3DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount) = 0;
			virtual void drawIndexedTriangleList(const S3DVertex2TCoords* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount) = 0;
			virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos) = 0;
			virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos,
				const core::rectEx<s32>& sourceRect, const core::rectEx<s32>* clipRect = 0,
				Color color = Color(255, 255, 255, 255), bool useAlphaChannelOfTexture = false) = 0;
			virtual void draw2DRectangle(Color color, const core::rectEx<s32>& pos, const core::rectEx<s32>* clip = 0) = 0;
			virtual core::dimension2d<s32> getScreenSize() = 0;
			virtual s32 getFPS() = 0;
			virtual u32 getPrimitiveCountDrawed() = 0;
			virtual void deleteAllDynamicLights() = 0;
			virtual void addDynamicLight(const SLight& light) = 0;
			virtual s32 getMaximalDynamicLightAmount() = 0;

		};
	}
}

