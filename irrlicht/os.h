//ÒÑÍê³É

#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace os
	{
		class warning
		{
		public:
			static void show(const c8* message, const c8* hint = 0);
			static void show(const wchar_t* message, const wchar_t* hint = 0);
			static void print(const c8* message, const c8* hint = 0);
		};
		class DebugInfo
		{
			static void print(const c8* message, const c8* hint = 0);
			static void print(const wchar_t* message, const wchar_t* hint = 0);
		};
		class Randomizer
		{
			static void reset();
			static s32 rand();
		private:
			static s32 _seed;
		};
		class Timer
		{
		public:
			static u32 getTime();
		};
	}
}