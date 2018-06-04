
#pragma once

#include "../../irrtypes.h"
namespace irr
{
	template <class  T>
	inline void heapsink(T * array, s32 element, s32 max)
	{
		while ( ( element << 1 ) < max ) 
		{
			s32 j = (element << 1);
			if ( j + 1 < max && array[j] < array[j+1] )
			{
				j = j + 1;
			}
			if ( array[element] < array[j] )
			{
				T t = array[j];
				array[j] = array[element];
				array[element] = t;
				element = j;
			}
			else
			{
				return;
			}
		}
	}

	template <class T>
	inline void heapsort(T * array, s32 size)
	{
		T * virtualArray = array - 1;
		s32 virtualSize = size + 2;
		for (s32 i = ((size-1)/2); i >= 0; i--)
		{
			heapsink(virtualArray, i + 1, virtualSize - 1);
		}
		for (size_t i = size - 1; i >= 0; i--)
		{
			T t = array[0];
			array[0] = array[i];
			array[i] = t;
			heapsink(virtualArray, 1, i + 1);
		}
	}
}