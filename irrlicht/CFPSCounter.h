#pragma once
#include "irrtypes.h"
namespace irr
{
	namespace video
	{
		class CFPSCounter
		{
		public:
			CFPSCounter();
			~CFPSCounter();
			//���ص�ǰfps
			s32 getFPS();
			//ÿ֡����
			void registerFrame(u32 now);

		private:
			s32 _fps;
			u32 _startTime;
			u32 _framesCounted;
		};

	}
}

