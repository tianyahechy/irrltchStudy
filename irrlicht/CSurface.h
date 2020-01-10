#pragma once
#include "ISurface.h"

namespace irr
{
	namespace video
	{
		class CSurface : public ISurface
		{
		public:
			CSurface(const core::dimension2d<s32>& size);
			virtual ~CSurface();

			virtual s16* lock();
			virtual void unlock();
			virtual const core::dimension2d<s32>& getDimension();
			virtual void setPixel(s32 x, s32 y, s16 color);
			virtual s16 getPixel(s32 x, s32 y);
			virtual s16 getRedMask() ;
			virtual s16 getGreenMask();
			virtual s16 getBlueMask();
			virtual s16 getAlphaMask();
			virtual void fill(s16 color);
			virtual void drawRectangle(const core::rectEx<s32>& rect, Color color);
			virtual void drawRectangle(s32 x, s32 y, s32 x2, s32 y2, Color color);
			virtual void copyTo(ISurface* target, s32 x, s32 y);
			virtual void copyTo(ISurface* target, const core::position2d<s32>& pos);
			virtual void copyTo(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect, const core::rectEx<s32>* clipRect = 0);
			virtual void copyToWithAlpha(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect);
			virtual void copyToWithAlpha(ISurface* target, const core::position2d<s32>& pos, const core::rectEx<s32>& sourceRect, s16 color, const core::rectEx<s32>* clipRect = 0);
			virtual void copyToScaling(ISurface * target);
			virtual void drawLine(const core::position2d<s32>& from, const core::position2d<s32>& to, s16 color);
			virtual void resizeTo(const core::dimension2d<s32>& size);

		private:
			inline void clipX(s32 &x);
			inline void clipY(s32 &y);
			inline void exchange(s32& a, s32& b);
			inline bool clipRect(const s32 targetWidth, const s32 targetHeight, s32& targetX, s32& targetY, s32& xInSource, s32& yInSource, s32& sourceWidth, s32& sourceHeight);
			inline void setPixelFast(s32 x, s32 y, s16 color);

			s16* _data;
			core::dimension2d<s32> _size;
			s32 _dataSize;
			s32 _dataSizeInBytes;
		};
	}
}