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
		private:
			int m_repeat;
		
		public:
			KeyPressedEvent(int button, int repeat);

			inline const int getRepeat() const { return m_repeat;  }
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int button);
		};
	}
}