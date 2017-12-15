#pragma once

//
// Created by adun on 2017. 11. 27..
//

#include "maths/maths.h"

#include "utils/fileutils.h"
#include "utils/timer.h"

#include "graphics/window.h"
#include "graphics/shaders/shader.h"
#include "graphics/shaders/shader_factory.h"

#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"

#include "graphics/bases/renderer2d.h"
#include "graphics/renderers/batchrenderer2d.h"

#include "graphics/sprite.h"

#include "graphics/layers/layer.h"

#include "graphics/layers/group.h"

#include "utils/imageload.h"

#include "graphics/texture.h"
#include "graphics/texture_manager.h"

#include "graphics/label.h"

#include "graphics/font.h"
#include "graphics/font_manager.h"

#include "utils/log.h"

#include "graphics/mask.h"

#include "graphics/mesh_factory.h"

#include "graphics/buffers/frameBuffer.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

namespace AdunGL
{
	class Adun
	{
	private:
		Window* m_window;
		Timer*  m_timer;

		unsigned int m_framesPerSecond, m_updatesPerSecond;

	protected:
		Adun()
			: m_framesPerSecond(0), m_updatesPerSecond(0)
		{

		}

		virtual ~Adun()
		{
			delete m_timer;
			delete m_window;
		}


		Window* createWindow(const char* name, int width, int height)
		{
			m_window = new graphics::Window(name, width, height);

			return m_window;
		}

	public:
		void start()
		{
			init();
			run();
		}

	protected:
		virtual void init() = 0;

		virtual void tick() { };

		virtual void update() {};

		virtual void render() = 0;

		const unsigned int getFPS() const { return m_framesPerSecond; }
		const unsigned int getUPS() const { return m_updatesPerSecond; }

	private:
		void run()
		{
			m_timer = new utils::Timer();

			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;

			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!m_window->closed())
			{
				m_window->clear();

				glutMainLoopEvent();

				if (m_timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}

				render();

				frames++;

				if (m_timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_framesPerSecond = frames;
					m_updatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}

				m_window->update();
			}
		}
	};
}

