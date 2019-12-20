#pragma once
#include "IUnknown.h"
#include "dimension2d.h"
#include "EDriverTypes.h"

namespace irr
{
	namespace video
	{
		enum ECOLOR_FORMAT
		{
			EHCF_R5G5B5 = 0,
			EHCF_R5G6B5,
			EHCF_A8R8G8B8,
		};
		class ITexture : public IUnkown
		{
		public:
			virtual ~ITexture() {};

			virtual void* lock() = 0;
			virtual void unlock() = 0;
			virtual const core::dimension2d<s32>& getDimension() = 0;
			virtual EDriverType getDriverType() = 0;
			virtual ECOLOR_FORMAT getColorFormat() = 0;
			virtual s32 getPitch() = 0;

		};
	}
}
