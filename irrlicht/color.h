#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace video
	{
		inline s16 RGB16(s32 r, s32 g, s32 b)
		{
			return (((r >> 3) & 0x1F) << 10) | (((g >> 3) & 0x1F) << 5) | ((b >> 3) & 0x1F);
		}
		inline s16 X8R8G8B8toAlR5G5B5(s32 color)
		{
			return RGB16(color >> 16, color >> 8, color);
		}
		inline s32 getRed(s16 color)
		{
			return ((color >> 10) & 0x1F);
		}
		inline s32 getGreen(s16 color)
		{
			return ((color >> 5) & 0x1F);
		}
		inline s32 getBlue(s16 color)
		{
			return ((color) & 0x1F);
		}
		inline s32 A1R5G5B5toA8R8G8B8(s16 color)
		{
			return (((color >> 15) & 0x1) << 31) | (((color >> 10) & 0x1F) << 19) | (((color >> 5) & 0x1F) << 11) | (color & 0x1F) << 3;
		}

		class Color
		{
			
		public:
			s32 _color;
			inline Color()
			{
			}
			inline Color(s32 a, s32 r, s32 g, s32 b)
			{
				_color = (((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
			}
			inline Color(s32 clr)
			{
				_color = clr;
			}
			inline s32 getAlpha() const
			{
				return (_color >> 24) & 0xff;
			}			
			inline s32 getRed() const
			{
				return (_color >> 16) & 0xff;
			}
			inline s32 getGreen() const
			{
				return (_color >> 8) & 0xff;
			}
			inline s32 getBlue() const
			{
				return _color  & 0xff;
			}
			inline void setAlpha(s32 a)
			{
				_color = (((a & 0xff) << 24) | (((_color >> 16 ) & 0xff) << 16) | (((_color>>8) & 0xff) << 8) | (_color & 0xff));
			}
			inline void setRed(s32 r)
			{
				_color = ((((_color >> 24) & 0xff) << 24) | ((r & 0xff) << 16) | (((_color >> 8) & 0xff) << 8) | (_color & 0xff));
			}
			inline void setGreen(s32 g)
			{
				_color = ((((_color >> 24) & 0xff) << 24) | (((_color >> 16) & 0xff) << 16) | ((g & 0xff) << 8) | (_color & 0xff));
			}
			inline void setBlue(s32 b)
			{
				_color = ((((_color >> 24) & 0xff) << 24) | (((_color >> 16) & 0xff) << 16) | (((_color >> 8) & 0xff) << 8) | (b & 0xff));
			}
			inline s16 toA1R5G5B5() const
			{
				return RGB16(_color >> 16, _color >> 8, _color);
			}
			inline s32 toOpenGLColor() const
			{
				return (((_color >> 24) & 0xff) << 24) |
					(((_color) & 0xff) << 16) |
					((_color >> 8 & 0xff) << 8) |
					((_color >> 16) & 0xff);
			}
			inline void set(s32 a, s32 r, s32 g, s32 b)
			{
				_color = (((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g < 0xff) << 8) | (b & 0xff));
			}
			inline bool operator== (const Color& other) const
			{
				return other._color == _color;
			}
			inline bool operator != (const Color& other) const
			{
				return other._color != _color;
			}
		};
	
		class Colorf
		{
		public:
			f32 _r;
			f32 _g;
			f32 _b;
			f32 _a;

			Colorf()
			{
				_r = 0.0;
				_g = 0.0;
				_b = 0.0;
				_a = 0.0;
			}
			Colorf(f32 r, f32 g, f32 b)
			{
				_r = r;
				_g = g;
				_b = b;
				_a = 1.0f;
			}
			Colorf(f32 r, f32 g, f32 b, f32 a)
			{
				_r = r;
				_g = g;
				_b = b;
				_a = a;
			}
			Colorf(Color c)
			{
				const f32 inv = 1.0f / 255.0f;
				_r = c.getRed() * inv;
				_g = c.getGreen() * inv;
				_b = c.getBlue() * inv;
				_a = c.getAlpha() * inv;
			}
			void set(f32 rr, f32 gg, f32 bb)
			{
				_r = rr;
				_g = gg;
				_b = bb;
			}
		};
	}
}