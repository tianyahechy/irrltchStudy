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
				Color color = Color(255, 255, 255, 255),
				bool useAlphaChannelOfTexture = false);
			virtual void draw2DRectangle(Color color, const core::rect<s32>& pos, const core::rectEx<s32>* clip = 0);

		protected:
			void setRenderTarget(video::ISurface* surface);
			void setTexture(video::ITexture* texture);
			video::ISurface* _backBuffer;
			video::ISurfacePresenter* _presenter;
			void switchToTriangleRenderer(ETriangleRenderer renderer);
			void selectRightTriangeRenderer();
			core::array<S2DVertex> _transformedPoints;
			video::ITexture* _renderTargetTexture;
			video::ISurface* _renderTargetSurface;
			core::position2d<s32> _renderTargetSize;
			core::dimension2d<s32> _viewportSize;
			core::matrix4 _transformationMatrix[TS_COUNT];
			IK3DtriangleRenderer* _currentTriangleRenderer;
			IK3DtriangleRenderer* _trangleRenderers[ETR_COUNT];
			ETriangleRenderer _currentRenderer;
			IZBuffer* _zBuffer;
			video::ITexture* _texture;
			SMaterial _material;


		};
	}
}
