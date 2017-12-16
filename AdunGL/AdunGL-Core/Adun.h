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

#include "graphics/postfx/post_effect_pass.h"
#include "graphics/postfx/post_effect.h"

#include "events/event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"

#include "graphics/layers/layer2d.h"

#include "graphics/shaders/shader_uniform.h"
#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/renderers/renderer3d.h"
#include "graphics/renderers/forward_renderer.h"

#include "graphics/scene.h"
#include "graphics/layers/layer3d.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;
using namespace events;

namespace AdunGL
{
	class Adun
	{
	private:
		static Adun* s_instance;

	public:
		Window* window;

	private:
		bool m_running, m_paused;

		Timer* m_timer;

		unsigned int m_framesPerSecond, m_updatesPerSecond;

		const char* m_name;

		GLuint m_width, m_height;

		std::vector<Layer*> m_layerStack;

	public:
		Adun(const char* name, int width, int height);
		virtual ~Adun();

		virtual void init();

		void pushLayer(Layer* layer);
		Layer* popLayer();

		void start();
		void pause();
		void resume();
		void stop();

	protected:
		void onTick();
		void onUpdate();
		void onRender();

	public:
		const unsigned int getFPS() const { return m_framesPerSecond; }
		const unsigned int getUPS() const { return m_updatesPerSecond; }

	private:
		void run();

	public:
		inline static Adun& getAdun() { return *s_instance; }
	};
}

