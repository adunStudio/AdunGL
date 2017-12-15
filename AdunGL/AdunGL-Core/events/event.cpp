#include "event.h"

namespace AdunGL
{
	namespace events
	{
		Event::Event(Type type)
			: m_type(type), m_handled(false)
		{

		}
	}
}