#pragma once

namespace AdunGL
{
	namespace events
	{
		class Event
		{
		public:
			enum class Type
			{
				MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVEDD,
				KEY_PRESSED, KEY_RELEASED
			};

		protected:
			bool m_handled;
			Type m_type;

		protected:
			Event(Type type);
			
			inline Type getType() const { return m_type; }
		};
	}
}