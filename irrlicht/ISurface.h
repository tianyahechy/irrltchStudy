#pragma once
#include "IUnknown.h"
#include "position2d.h"
#include "rect.h"
#include "color.h"

namespace irr
{
	namespace video
	{
		class ISurface : public IUnkown
		{
		public:
			virtual ~ISurface()
			{
			}

			virtual s16* lock() = 0;
			virtual void unlock() = 0;
			virtual const core::dimension2d<s32>& getDimension() = 0;
			virtual void setPixel(s32 x, s32 y, s16 color) = 0;
			virtual s16 getPixel(s32 x, s32 y) = 0;
			virtual s16 getRedMask() = 0;
			virtual s16 getGreenMask() = 0;
			virtual s16 getBlueMask() = 0;
			virtual s16 getAlphaMask() = 0;
			virtual void fill(s16 color) = 0;
			virtual void drawRectangle(const core::rectEx<s32>& rect, Color color) = 0;
			virtual void drawRectangle(s32 x, s32 y, s32 x2, s32 y2, Color color) = 0;
			virtual void copyTo(ISurface* target, s32 x, s32 y) = 0;
			virtual void copyTo(ISurface* target, const core::position2d<s32>& pos) = 0;
			virtual void copyTo(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect, const core::rectEx<s32>* clipRect = 0) = 0;
			virtual void copyToWithAlpha(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect) = 0;
			virtual void copyToWithAlpha(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect, s16 color, const core::rectEx<s32>* clipRect = 0) = 0;
			virtual void copyToScaling(ISurface * target) = 0;
			virtual void drawLine(const core::position2d<s32>& from, const core::position2d<s32>& to, s16 color) = 0;
			virtual void resizeTo(const core::dimension2d<s32>& size) = 0;
		};
		ISurface* createSurface(const core::dimension2d<s32>& size);
	}
}