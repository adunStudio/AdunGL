#pragma once

#include "event.h"

namespace AdunGL
{
	namespace events
	{
		class KeyEvent : public Event
		{
		private:
			int m_keyCode;

		public:
			KeyEvent(int keyCode, Event::Type type);

			inline const int getKeyCode() const { return m_keyCode; }
		};

		class KeyPressedEvent : public KeyEvent
		{

		};

		class KeyReleasedEvent : public KeyEvent
		{

		};
	}
}