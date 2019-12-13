//ÒÑÍê³É

#pragma once
#include <stdlib.h>
#include "irrtypes.h"
#include <math.h>

namespace irr
{
	namespace core
	{
		const f32 fast_atof_table[] = 
		{
			0.f,
			0.1f,
			0.01f,
			0.001f,
			0.0001f,
			0.00001f,
			0.000001f,
			0.0000001f,
			0.00000001f,
			0.000000001f,
			0.0000000001f,
			0.00000000001f,
			0.000000000001f,
			0.0000000000001f,
			0.00000000000001f,
			0.000000000000001f
		};
		
		inline f32 fast_atof(const c8* c)
		{
			bool inv = false;
			c8 * t;
			f32 f;
			if ( *c == '-')
			{
				c++;
				inv = true;
			}

			f = (f32)strtol(c, &t, 10);
			c = t;
			if (*t == '.')
			{
				c++;
				f32 p1 = (f32)strtol(c, &t, 10);
				p1 *= fast_atof_table[t - c];

				f += p1;
				c = t;
				
				if (*c == 'e')
				{
					++c;
					f32 exp = (f32)strtol(c, &t, 10);
					f *= (f32)pow(10, exp);
				}
			}
		
			if (inv)
			{
				f *= -1.0f;
			}

			return f;
		}
	}
}