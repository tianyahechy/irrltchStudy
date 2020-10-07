#pragma once
#include "IUnknown.h"
#include "ISurface.h"
#include "S2DVertex.h"
#include "rect.h"
#include "IZBuffer.h"
#include "ISurface.h"

namespace irr
{
	namespace video
	{
		enum ETriangleRenderer
		{
			ETR_FLAT = 0,
			ETR_FLAT_WIRE,
			ETR_GOURAUD,
			ETR_GOURAUD_WIRE,
			ETR_TEXTURE_FLAT,
			ETR_TEXTURE_FLAT_WIRE,
			ETR_TEXTURE_GOURAUD,
			ETR_TEXTURE_GOURAUD_WIRE,
			ETR_COUNT

		};
		class IK3DtriangleRenderer : public IUnkown
		{
		public:
			virtual ~IK3DtriangleRenderer() {}
			virtual void setRenderTarget(video::ISurface* surface, const core::rectEx<s32>& viewPort) = 0;
			virtual void setBackfaceCulling(bool enable = true) = 0;
			virtual void setTexture(video::ISurface* texture) = 0;
			virtual void drawIndexedTriangleList(S2DVertex* vertices, s32 vertexCount, const u16* indexList, s32 triangleCount) = 0;

			IK3DtriangleRenderer* createTriangleRendererTextureGouraud(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererTextureGouraudWire(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererGouraud(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererGouraudWire(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererTextureFlat(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererTextureFlatWire(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererFlat(IZBuffer* zBuffer);
			IK3DtriangleRenderer* createTriangleRendererFlatWire(IZBuffer* zBuffer);

		};
	}
}