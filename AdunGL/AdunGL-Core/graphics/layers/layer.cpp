//
// Created by adun on 2017. 11. 20..
//

#include "layer.h"

namespace AdunGL
{
	namespace graphics
	{
		Layer::Layer()
			: m_window(Window::instance)
		{
			
		}

		Layer::~Layer()
		{

		}

		void Layer::init()
		{

		}

		bool Layer::onEvent(const events::Event& event)
		{
			return false;
		}

		void Layer::onTick()
		{

		}

		void Layer::onUpdate()
		{

		}

		void Layer::onRender()
		{

		}
	}
}