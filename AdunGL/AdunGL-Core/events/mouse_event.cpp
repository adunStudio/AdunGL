#include "mouse_event.h"

namespace AdunGL
{
	namespace events
	{
		MouseButtonEvent::MouseButtonEvent(int button, float x, float y, Type type)
			: Event(type), m_button(button), m_position(maths::vec2(x, y))
		{

		}

		MousePressedEvent::MousePressedEvent(int button, float x, float y)
			: MouseButtonEvent(button, x, y, Event::Type::MOUSE_PRESSED)
		{

		}

		MouseReleasedEvent::MouseReleasedEvent(int button, float x, float y)
			: MouseButtonEvent(button, x, y, Event::Type::MOUSE_RELEASED)
		{

		}

		MouseMovedEvent::MouseMovedEvent(float x, float y, bool dragged)
			: Event(Event::Type::MOUSE_MOVEDD), m_position(maths::vec2(x, y)), m_dragged(dragged)
		{

		}
	}
}