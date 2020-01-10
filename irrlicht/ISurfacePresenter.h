#pragma once
#include "ISurface.h"

namespace irr
{
	namespace video
	{
		class ISurfacePresenter
		{
		public:
			virtual void present(video::ISurface* surface) = 0;
		};
	}
}