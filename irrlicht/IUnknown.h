//ÒÑÍê³É

#pragma once
#include "irrtypes.h"
namespace irr
{
	class IUnkown
	{
	private:
		s32 ReferenceCounter;
		const c8* DebugName;

	public:
		IUnkown()
		{
			ReferenceCounter = 1;
			DebugName = 0;
		}
		virtual ~IUnkown()
		{

		}
		void grab()
		{
			++ReferenceCounter;
		}
		bool drop()
		{
			--ReferenceCounter;
			if (!ReferenceCounter)
			{
				delete this;
				return true;
			}
			return false;
		}
		const c8 * getDebugName() const
		{
			return DebugName;
		}
	protected:
		void setDebugName(const c8* newName)
		{
			DebugName = newName;
		}
	};
}
