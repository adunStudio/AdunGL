#pragma once

#include "event.h"

namespace AdunGL
{
	namespace events
	{
		// �������̽�
		class IEventListener
		{
		public:
			virtual bool onEvent(const Event& event) = 0;
		};
	}
}