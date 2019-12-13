//ÒÑÍê³É

#include "os.h"
#include <stdio.h>

#include <Windows.h>

namespace irr
{
	namespace os
	{
		void DebugInfo::print(const c8* message, const c8* hint)
		{
			size_t hs = hint ? strlen(hint) : 0;
			c8* tmp = new c8[strlen(message) + hs + 14];
			sprintf(tmp, "%s%s%s\n", message, hint ? ":" : " ", hint ? hint : " ");
			OutputDebugStringA(tmp);
			delete[] tmp;
		}
		void DebugInfo::print(const wchar_t* message, const wchar_t* hint)
		{
			size_t hs = hint ? wcslen(hint) : 0;
			wchar_t* tmp = new wchar_t[wcslen(message) + hs + 14];
			swprintf(tmp, L"%s%s%s\n", message, hint ? ":" : " ", hint ? hint : " ");
			OutputDebugStringW(tmp);
			delete[] tmp;
		}
		void warning::show(const c8 * warning, const c8* hint)
		{
			if (hint)
			{
				c8* tmp = new c8[strlen(warning) + strlen(hint) + 2];
				sprintf(tmp, "%s\n%s", warning, hint);
				MessageBoxA(0, tmp, "Warning!", MB_OK);
				delete[] tmp;
			}
			else
			{
				MessageBoxA(0, warning, "Warning!", MB_OK);
			}
		}
		void warning::show(const wchar_t * warning, const wchar_t* hint)
		{
			if (hint)
			{
				wchar_t* tmp = new wchar_t[wcslen(warning) + wcslen(hint) + 2];
				swprintf(tmp, L"%s\n%s", warning, hint);
				MessageBoxW(0, tmp, L"Warning!", MB_OK);
				delete[] tmp;
			}
			else
			{
				MessageBoxW(0, warning, L"Warning!", MB_OK);
			}
		}
		void warning::print(const c8* message, const c8* hint)
		{
			size_t hs = hint ? strlen(hint) : 0;
			c8* tmp = new c8[strlen(message) + hs + 14];
			sprintf(tmp, "%s%s%s\n", message, hint ? ":" : " ", hint ? hint : " ");
			OutputDebugStringA(tmp);
			delete[] tmp;
		}
		u32 Timer::getTime()
		{
			return GetTickCount();
		}
	}
	
	namespace os
	{
		s32 Randomizer::_seed = 0x0f0f0f0f;
		s32 Randomizer::rand()
		{
			const s32 m = 2147483399;
			const s32 a = 40692;
			const s32 q = 52774;
			const s32 r = 3791;

			_seed = a * (_seed % q) - r * (_seed / q);
			if (_seed < 0)
			{
				_seed += m;
			}
			return _seed;
		}
		void Randomizer::reset()
		{
			_seed = 0x0f0f0f0f;
		}
	}
}