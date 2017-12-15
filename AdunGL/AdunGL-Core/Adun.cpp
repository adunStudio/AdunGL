#include "Adun.h"

namespace AdunGL
{
	Adun* Adun::s_instance = nullptr;

	Adun::Adun(const char* name, int width, int height)
		: m_name(name), m_width(width), m_height(height)
	{
		s_instance = this;
	}

	Adun::~Adun()
	{
		delete window;
	}

	void Adun::init()
	{
		window = new Window(m_name, m_width, m_height);
	}

	void Adun::pushLayer(Layer* layer)
	{
		m_layerStack.push_back(layer);
		//layer->init();
	}

	Layer* Adun::popLayer()
	{
		Layer* layer = m_layerStack.back();
		m_layerStack.pop_back();
		return layer;
	}

	void Adun::onTick()
	{
		for (auto layer : m_layerStack)
			layer->onTick();
	}

	void Adun::onUpdate()
	{
		for (auto layer : m_layerStack)
			layer->onUpdate();
	}

	void Adun::onRender()
	{
		for (auto layer : m_layerStack)
			layer->onRender();
	}

	void Adun::start()
	{
		init();
		m_running = true;
		m_paused = false;
		run();
	}

	void Adun::pause()
	{
		m_paused = true;
	}

	void Adun::resume()
	{
		m_paused = false;
	}

	void Adun::stop()
	{
		m_running = false;
	}

	void Adun::run()
	{
		m_timer = new utils::Timer();

		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;

		unsigned int frames = 0;
		unsigned int updates = 0;

		while (m_running)
		{
			window->clear();

			glutMainLoopEvent();

			if (m_timer->elapsed() - updateTimer > updateTick)
			{
				onUpdate();
				updates++;
				updateTimer += updateTick;
			}

			onRender();

			frames++;

			if (m_timer->elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				frames = 0;
				updates = 0;
				onTick();
			}

			
			if (window->closed())
				m_running = false;
		}
	}
	
}