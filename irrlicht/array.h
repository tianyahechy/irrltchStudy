//ÒÑÍê³É

#pragma once

#include "irrtypes.h"
#include "heapsort.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class array
		{	
		private:
			T* data;
			u32 allocated;
			u32 used;
			bool free_when_destroyed;
			bool is_sorted;
		public:
			array()
				: data(0), used(0), allocated(0), free_when_destroyed(true), is_sorted(true)
			{

			}
			array(u32 start_count)
				: data(0), used(0), allocated(0), free_when_destroyed(true), is_sorted(true)
			{
				reallocate(start_count);
			}
			array(const array<T>& other)
				:data(0)
			{
				*this = other;
			}
			~array()
			{
				if (free_when_destroyed)
				{
					delete[] data;
				}
			}
			void reallocate(u32 new_size)
			{
				T * old_data = data;
				data = new T[new_size];
				allocated = new_size;
				s32 end = used < new_size ? used : new_size;
				for (s32 i = 0; i < end; i++)
				{
					data[i] = old_data[i];
				}
				if (allocated < used)
				{
					used = allocated;
				}
				delete[] old_data;
			}
	
			void push_back(const T& element)
			{
				if (used + 1 > allocated)
				{
					reallocate(used * 2 + 1);
				}
				data[used++] = element;
				is_sorted = false;
			}
			void clear()
			{
				delte[] data;
				data = 0;
				used = 0;
				allocated = 0;
				is_sorted = true;
			}

			void set_pointer(T* newPointer, u32 size)
			{
				delete[] data;
				data = newPointer;
				allocated = size;
				used = size;
				is_sorted = false;
			}
			void set_free_when_destroyed(bool f)
			{
				free_when_destroyed = f;
			}

			void set_used(u32 usedNow)
			{
				if (allocated < usedNow)
				{
					reallocate(usedNow);
				}
				used = usedNow;
			}
			void operator= (const array<T>& other)
			{
				if (data)
				{
					delete[] data;
				}
				data = new T[other.allocated];
				used = other.used;
				free_when_destroyed = other.free_when_destroyed;
				is_sorted = other.is_sorted;
				allocated = other.allocated;
				for (u32 i = 0; i < other.used; i++)
				{
					data[i] = other.data[i];
				}

			}
	
			T& operator[] (u32 index)
			{
				return data[index];
			}
			const T& operator[] (u32 index) const
			{
				return data[index];
			}
			T * pointer()
			{
				return data;
			}
			const T * const_pointer() const
			{
				return data;
			}
			u32 size() const
			{
				return used;
			}
			u32 allocated_size() const
			{
				return allocated;
			}
			bool empty() const
			{
				return used == 0;
			}
			void sort()
			{
				if (is_sorted || used < 2)
				{
					return;
				}
				heapsort(data, used);
				is_sorted = true;
			}
			s32 binary_search(const T& element, s32 left, s32 right)
			{
				if ( !used)
				{
					return -1;
				}
				sort();
				s32 m;
				do
				{
					m = (left + right) >> 1;
					if (element < data[m])
					{
						right = m - 1;
					}
					else
					{
						left = m + 1;
					}
				} while( (element < data[m] || data[m] < element) && left <= right );
				if (!(element < data[m]) && !(data[m] < element))
				{
					return m;
				}
				return -1;
			}

			s32 binary_search(const T& element)
			{
				return binary_search(element, 0, used - 1);
			}
			void erase(u32 index)
			{
				for (u32 i = index+1; i < used; i++)
				{
					data[i - 1] = data[i];
				}
				--used;
			}
			void erase(u32 index, s32 count)
			{
				for (u32 i = index + count; i < used; i++)
				{
					data[i - count] = data[i];
					used -= count
				}
			}
		};



	}
}