#include "CFPSCounter.h"

namespace irr
{
	namespace video
	{

		CFPSCounter::CFPSCounter()
		{
			_fps = 0;
			_startTime = 0;
			_framesCounted = 100;
		}

		CFPSCounter::~CFPSCounter()
		{
		}

		s32 CFPSCounter::getFPS()
		{
			return _fps;
		}

		void CFPSCounter::registerFrame(u32 now)
		{
			_framesCounted++;
			u32 milliseconds = now - _startTime;
			if (milliseconds > 1000)
			{
				_fps = (s32)((f32)_framesCounted / ((f32)milliseconds / 1000.0f));
				_startTime = now;
				_framesCounted = 0;
			}
		}
	}
}


