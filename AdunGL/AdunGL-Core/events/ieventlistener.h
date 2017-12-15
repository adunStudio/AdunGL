#pragma once

#include "event.h"

namespace AdunGL
{
	namespace events
	{
		// 인터페이스
		class IEventListener
		{
		public:
			virtual void onEvent(const Event& event) = 0;
		};
	}
}