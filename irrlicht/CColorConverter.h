#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace video
	{
		class CColorConverter
		{
		public:
			CColorConverter();
			~CColorConverter();

		public:
			static void convert4BitTo16BitFlipMirror(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert8BitTo16BitFlipMirror(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert1BitTo16BitFlipMirror(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert24BitTo16BitFlipMirror(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert24BitTo16BitColorShuffle(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert24BitTo16BitFlipColorShuffle(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert32BitTo16BitFlipColorShuffle(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert32BitTo16BitFlipMirrorColorShuffle(const c8* in, s16* out, s32 width, s32 height, s32 pitch, const s32* palette);
			static void convert16BitToA8R8G8B8andResize(const s16* in, s32* out, s32 newWidth, s32 newHeight, s32 currentWidth, s32 currentHeight);
			 
		};

	}
}

