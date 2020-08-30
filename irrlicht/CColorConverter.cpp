#include "CColorConverter.h"
#include "color.h"

namespace irr
{
	namespace video
	{
		CColorConverter::CColorConverter()
		{
		}


		CColorConverter::~CColorConverter()
		{
		}

		void CColorConverter::convert4BitTo16BitFlipMirror(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			s32 shift = 0;
			out += width * height;
			s16 * oout = out;
			for (s32 y = 0; y < height; y++)
			{
				shift = 4;
				out = oout - y * width - width;
				for (s32 x = 0; x < width; x++)
				{
					*out = X8R8G8B8toAlR5G5B5(palette[(u8)((*in >> shift) & 0xf)]);
					++out;
					shift -= 4;
					if (shift < 0)
					{
						shift = 4;
						++in;
					}
				}
				if (shift != 4)
				{
					++in;
				}
				in += pitch;
			}

		}
		void CColorConverter::convert8BitTo16BitFlipMirror(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			out += width * height;
			s32 lineWidth = width + pitch;
			const c8* p = in;
			for (s32 y = 1; y <= height; y++)
			{
				p = in + lineWidth * y - pitch;
				for (s32 x = 0; x < width; x++)
				{
					--out;
					--p;
					*out = X8R8G8B8toAlR5G5B5(palette[(u8)(*p)]);
				}
			}
		}
		void CColorConverter::convert1BitTo16BitFlipMirror(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			s16 * p = out + width * height;
			for (s32 y = 0; y < height; y++)
			{
				s32 shift = 7;
				out = p - y * width - width;
				for (s32 x = 0; x < width; x++)
				{
					*out = *in >> shift & 0x01 ? (s16)0xffff : (s16)0x0000;
					++out;
					--shift;
					if (shift < 0)
					{
						shift = 7;
						++in;
					}
				}
				if (shift != 7)
				{
					++in;
				}
				in += pitch;
			}
		}
		void CColorConverter::convert24BitTo16BitFlipMirror(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			const c8* p = in;
			const s32 lineWidth = 3 * width + pitch;
			out += width * height;
			for (s32 y = 0; y < height; y++)
			{
				for (s32 x = 0; x < width; x++)
				{
					p = in + (width - x - 1) * 3;
					--out;
					*out = RGB16(p[2], p[1], *p);
				}
				in += lineWidth;
			}
		}
		void CColorConverter::convert24BitTo16BitColorShuffle(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			const c8* p = in;
			const s32 lineWidth = 3 * width + pitch;
			for (s32 y = 0; y < height; y++)
			{
				for (s32 x = 0; x < width; x++)
				{
					p = in + (width - x - 1) * 3;
					*out = RGB16(*p, p[1], p[2]);
					++out;
				}
				in += lineWidth;
			}

		}
		void CColorConverter::convert24BitTo16BitFlipColorShuffle(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			const c8* p = in;
			const s32 lineWidth = 3 * width + pitch;
			for (s32 y = 0; y < height; y++)
			{
				for (s32 x = 0; x < width; x++)
				{
					p = in + (x) * 3;
					*out = RGB16(*p, p[1], p[2]);
					++out;
				}
				in += lineWidth;
			}

		}
		void CColorConverter::convert32BitTo16BitFlipColorShuffle(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			const c8* p = in;
			const s32 lineWidth = 4 * width + pitch;
			for (s32 y = 0; y < height; y++)
			{
				for (s32 x = 0; x < width; x++)
				{
					p = in + (width - x - 1) * 4;
					*out = RGB16(p[2], p[1], p[0]);
					++out;
				}
				in += lineWidth;
			}
		}
		void CColorConverter::convert32BitTo16BitFlipMirrorColorShuffle(const c8 * in, s16 * out, s32 width, s32 height, s32 pitch, const s32 * palette)
		{
			const c8* p = in;
			const s32 lineWidth = 4 * width + pitch;
			out += (width + pitch) * height;
			for (s32 y = 0; y < height; y++)
			{
				for (s32 x = 0; x < width; x++)
				{
					p = in + (width - x - 1) * 4;
					--out;
					*out = RGB16(p[2], p[1], p[0]);
				}
				in += lineWidth;
			}
		}
		void CColorConverter::convert16BitToA8R8G8B8andResize(const s16 * in, s32 * out, s32 newWidth, s32 newHeight, s32 currentWidth, s32 currentHeight)
		{
			if (!newWidth || !newHeight)
			{
				return;
			}
			s32 nDataSize = newWidth * newHeight;
			s32 nDataSizeInBytes = nDataSize * sizeof(s32);

			f32 sourceXStep = (f32)currentWidth / (f32)newWidth;
			f32 sourceYStep = (f32)currentHeight / (f32)newHeight;

			for (s32 x = 0; x < newWidth; x++)
			{
				f32 sy = 0.0f;
				for (s32 y = 0; y < newHeight; y++)
				{
					s32 t = in[(s32)(((s32)sy) * currentWidth + x * sourceXStep)];
					t = (((t >> 15) & 0x1) << 31) | (((t >> 10) & 0x1F) << 19) |
						(((t >> 5) & 0x1F) << 11) | (t & 0x1F) << 3;
					out[(s32)(y* newWidth + x)] = t;
					sy += sourceYStep;
				}
			}
		}
	}
}
