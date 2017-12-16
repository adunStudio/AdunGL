#pragma once

//
// Created by adun on 2017. 11. 20..
//

#include "../../events/event.h"
#include "../../events/ieventlistener.h"
#include "../window.h"

namespace AdunGL
{
	namespace graphics
	{
		class Layer : public events::IEventListener
		{
		protected:
			Window* m_window;

		public:
			Layer();
			virtual ~Layer();

			virtual void init();
			virtual bool onEvent(const events::Event& event);
			virtual void onTick();
			virtual void onUpdate();
			virtual void onRender();
		};
	}
}
