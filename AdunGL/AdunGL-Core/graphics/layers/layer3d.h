#pragma once

#include "layer.h"
#include "../scene.h"

namespace AdunGL
{
	namespace graphics
	{
		class Layer3D : public Layer
		{
		protected:
			Scene* m_scene;
			Renderer3D* m_renderer;

		public:
			Layer3D(Scene* scene);
			~Layer3D();

			virtual void init();
			virtual void onInit(Renderer3D& renderer, Scene& scene);

			inline Scene* getScene() const { return m_scene; }
			
			void onRender() override;
			virtual void onRender(Renderer3D& renderer);
		};
	}
}