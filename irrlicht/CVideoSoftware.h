#pragma once
#include "IK3DtriangleRenderer.h"
#include "CVideoNull.h"

namespace irr
{
	namespace video
	{
		class CVideoSoftware : public CVideoNull
		{
		public:
			CVideoSoftware(
				const core::dimension2d<s32>& windowSize,
				bool fullScreen, io::IFileSystem* io, 
				video::ISurfacePresenter* presenter);

			virtual ~CVideoSoftware();
			virtual bool endScene();
			virtual bool queryFeature(EK3D_VIDEO_DRIVER_FEATRUE feature);
			virtual void setTransform(E_TRANSOFRMATION_STATE state, const core::matrix4& mat);
			virtual void setMaterial(const SMaterial& material);
			virtual void setRenderTarget(video::ITexture* texture);
			virtual void setViewPort(const core::rectEx<s32>& area);
			virtual bool beginScene(bool backBuffer, bool zBuffer, Color color);
			virtual void drawIndexedTriangleList(const S3DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount);
			virtual void drawIndexedTriangleList(const S3DVertex2TCoords* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount);
			virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos);
			virtual void draw2DImage(
				video::ITexture* texture,
				const core::position2d<s32>& destPos,
				const core::rectEx<s32>& sourceRect,
				const core::rectEx<s32>* clipRect = 0,
				Color color = )


		};
	}
}
