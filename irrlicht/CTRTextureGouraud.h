#pragma once
#include "IK3DtriangleRenderer.h"
#include "rect.h"
namespace irr
{
	namespace video
	{
		class CTRTextureGouraud : public IK3DtriangleRenderer
		{
		public:
			CTRTextureGouraud(IZBuffer* zbuffer);
			virtual ~CTRTextureGouraud();

			virtual void setRenderTarget(video::ISurface* surface, const core::rectEx<s32>& viewPort);
			virtual void setBackfaceCulling(bool enable = true);
			virtual void setTexture(video::ISurface* texture);
			virtual void drawIndexedTriangleList(S2DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount);

		protected:
			inline void swapVertices(const S2DVertex** v1, const S2DVertex** v2)
			{
				const S2DVertex* b = *v1;
				*v1 = *v2;
				*v2 = b;
			}
			video::ISurface* _renderTarget;
			core::rectEx<s32> _viewPortRect;
			IZBuffer* _zbuffer;
			s32 _surfaceWidth;
			s32 _surfaceHeight;
			bool _backFaceCullingEnabled;
			TZBufferType* _lockedZBuffer;
			u16* _lockedSurface;
			s16* _lockedTexture;
			s32 _lockedTextureWidth;
			s32 _textureXMask, _textureYMask;
			video::ISurface* _texture;

		};

	}
}