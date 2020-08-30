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
			//返回当前fps
			s32 getFPS();
			//每帧更新
			void registerFrame(u32 now);

		private:
			s32 _fps;
			u32 _startTime;
			u32 _framesCounted;
		};

	}
}

