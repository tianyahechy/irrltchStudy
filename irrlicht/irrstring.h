//已完成

#pragma once

#include "irrtypes.h"
namespace irr
{
	namespace core
	{
		template <class T>
		class string
		{
		private:
			T * _array;
			s32 _allocated;
			s32 _used;

			//תСд
			T toLower(const T& t) const
			{
				if (t > (T)'A' && t <= (T)'Z')
				{
					return t + ((T)'a' - (T)'A');
				}
				else
				{
					return t;
				}
			}

			s32 size() const
			{
				return _used - 1;
			}
			const T* c_str() const
			{
				return _array;
			}
			void reallocate(s32 new_size)
			{
				T * old_array = _array;
				_array = new T[new_size];
				_allocated = new_size;
				s32 amount = _used < new_size ? _used : new_size;
				for (s32 i = 0; i < amount; i++)
				{
					_array[i] = old_array[i];
				}
				if (_allocated < _used)
				{
					_used = _allocated;
				}
				delete[] old_array;

			}
		public:
			string()
			{
				_allocated = 1;
				_used = 1;
				_array = 0;
				_array = new T[1];
				_array[0] = 0x0;
			}
			string(const string<T>& other)
			{
				_allocated = 0;
				_used = 0;
				_array = 0;
				*this = other;
			}

			template <class B>
			string(const B* c)
			{
				_allocated = 0;
				_used = 0;
				_array = 0;
				*this = c;
			}
			~string()
			{
				delete[] _array;
			}
			string<T>& operator= (const string<T>& other)
			{
				if (this == &other)
				{
					return*this;
				}
				delete[] _array;
				_allocated = _used = other.size() + 1;
				_array = new T[_used];

				const T* p = other.c_str();
				for (size_t i = 0; i < _used; i++, p++)
				{
					_array[i] = *p;
				}
				return *this;
			}
			template <class B>
			string<T>& operator= (const B* c)
			{
				if (!c)
				{
					_array[0] = 0x0;
					return *this;
				}

				if ((void*) c == ( void*) _array )
				{
					return *this;
				}
				s32 len = 0;
				const B* p = c;
				while (*p)
				{
					++len;
					++p;
				}
				T * oldArray = _array;
				_allocated = _used = len + 1;
				_array = new T[_used];
				for (s32 i = 0; i < len; i++)
				{
					_array[i] = (T)c[i];
				}
				delete[] oldArray;
				return *this;
			}
			string<T> operator+ (const string<T>& other)
			{
				--_used;
				s32 len = (s32)other.size() + 1;
				if (_used + len > _allocated)
				{
					reallocate((s32)_used + len);
				}
				const T * p = other.c_str();
				for (s32 i = 0; i < len; i++, ++p)
				{
					_array[_used + i] = *p;
				}
				_used = _used + len;
				return *this;
			}
			template <class B>
			string<T>& operator+ (const B* c)
			{
				--_used;
				s32 len = 0;
				const B* p = c;
				while ( *p)
				{
					++len;
					++p;
				}
				++len;
				if (_used + len > _allocated)
				{
					reallocate((s32)_used +(s32) len);
				}
				for (s32 i = 0; i < len; i++, ++p)
				{
					_array[_used + i] = (T) c[i];
				}
				_used = _used + len;
				return *this;
			}
			
			T& operator[] (const s32 index) const
			{
				#ifdef _DEBUG
				if (index >= _used)
				{
					_asm int 3
				}
				#endif // _DEBUG
				return _array[index];

			}

			bool operator== (const string<T>& other) const
			{
				for (s32 i1 = 0, i2 = 0; _array[i1] && other._array[i2]; i1++, i2++)
				{
					if (_array[i1] != other._array[i2])
					{
						return false;
					}
				}
				return _used == other._used;
			}
			
			bool operator< (const string<T>& other) const
			{
				for (s32 i1 = 0, i2 = 0; _array[i1] && other._array[i2]; i1++, i2++)
				{
					if (_array[i1] != other._array[i2])
					{
						return (_array[i1] < other._array[i2]);
					}
				}
				return _used < other._used;
			}

			bool operator != (const string<T>& other) const
			{
				return !(*this == other);
			}

			void make_lower()
			{
				const T A = (T) 'A';
				const T Z = (T) 'Z';
				const T diff = (T) 'a' - A;
				for (s32 i = 0; i < _used; i++)
				{
					if (_array[i] >= A && _array[i] <= Z)
					{
						_array[i] += diff;
					}
				}
			}

			void make_upper()
			{
				const T a = (T) 'a';
				const T z = (T) 'z';
				const T diff = (T) 'A' - a;
				for (s32 i = 0; i < _used; i++)
				{
					if (_array[i] >= a && _array[i] <= z)
					{
						_array[i] += diff;
					}
				}
			}
		
			bool equal_ignore_case(const string<T>& other) const
			{
				for (s32 i1 = 0, i2 = 0; _array[i1] && other._array[i2]; i1++, i2++)
				{
					if (toLower( _array[i1]) != toLower( other._array[i2]))
					{
						return false;
					}
				}
				return _used == other._used;
			}

			void append(T character)
			{
				if (_used + 1 > _allocated)
				{
					reallocate((s32)_used + 1);
				}
				_used += 1;
				_array[_used - 2] = character;
				_array[_used - 1] = 0;
			}

			void append(const string<T>& other)
			{
				--_used;
				s32 len = other.size();
				if (_used + len + 1 > _allocated)
				{
					reallocate((s32)_used + (s32)len + 1);
				}
				for (s32 i = 0; i < len + 1; i++)
				{
					_array[i + _used] = other[i];
				}
				_used = _used + len + 1;
			}

			void append(const string<T>& other, s32 length)
			{
				s32 len = other.size();
				if (len < length)
				{
					append(other);
					return;
				}
				len = length;
				--_used;
				if (_used + len > _allocated)
				{
					reallocate((s32)_used + (s32)len);
				}
				for (s32 i = 0; i < len; i++)
				{
					_array[i + _used] = other[i];
				}
				_used = _used + len;
			}
			void reserve(s32 count)
			{
				if (count < _allocated)
				{
					return;
				}
				reallocate(count);
			}
		};


	}
}
