#include <iostream>
#include <vector>
#include "../AdunGL-Core/Adun.h"

#define WIDTH 1280
#define HEIGHT 720

class Game : public Adun
{
private:
	Layer*  layer;
	Label*  fps;
	Sprite* sprite;
	Shader* shader;
	Mask*   mask;
	Label** debugInfo;

public:
	Game()
		: Adun("AdunGL Test Game", WIDTH, HEIGHT)
	{

	}

	~Game()
	{
		delete layer;
	};

	void init() override
	{

		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		
		shader = ShaderFactory::DefaultShader();
		
		layer = new Layer(new BatchRenderer2D(maths::tvec2<GLuint>(WIDTH, HEIGHT)), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->renderer->setRenderTarget(RenderTarget::BUFFER);
		layer->renderer->addPostEffectsPass(new PostEffectsPass(Shader::FromFile("MyGame/Shaders/postfx.vert", "MyGame/Shaders/postfx.frag")));
		layer->renderer->setPostEffects(true);


		Texture::setFIlter(TextureFilter::NEARST);
		TextureManager::add(new Texture("Basic", "MyGame/Asset/images/tb.png"));
		sprite = new Sprite(0, 0, 8, 8, TextureManager::get("Basic"));
		layer->add(sprite);
		layer->add(new Sprite(-8.0f, -8.0f, 6, 6, maths::vec4(1, 1, 0, 0)));

		fps = new Label("", -15.5f, 7.8f, maths::vec4(0, 1, 1, 1));
		layer->add(fps);

		debugInfo = new Label*[10];
		debugInfo[0] = new Label("", -15.5f, 6.8f, "arial", maths::vec4(1, 1, 0, 1));
		debugInfo[1] = new Label("", -15.5f, 5.8f, "arial", maths::vec4(1, 1, 0, 1));
		layer->add(debugInfo[0]);
		layer->add(debugInfo[1]);


		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		mask = new Mask(new Texture("Mask", "MyGame/Asset/images/mask.png"));
		mask->transform = mat4::translation(vec3(-16.0f, -9.0f, 0.0f)) * mat4::scale(vec3(32, 18, 1));

		layer->setMask(mask);
		

	}

	void tick() override // 1초 마다 실행
	{
		fps->text = std::to_string(getFPS()) + " fps";
		ADUNGL_INFO("%d ups, %d fps", getUPS(), getFPS());
	}

	void update() override // frame마다 실행
	{
		if (window->isKeyPressed('t'))
		{
			layer->renderer->setRenderTarget(layer->renderer->getRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);

		}
		if (window->isKeyPressed('p'))
		{
			layer->renderer->setPostEffects(!layer->renderer->getPostEffects());
		}
		
	

		debugInfo[0]->text = std::string("Target: ") + (layer->renderer->getRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
		debugInfo[1]->text = std::string("PostFX: ") + (layer->renderer->getPostEffects() ? "On" : "Off");
	}


	void render() override
	{
		layer->render();
	}
};


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	Game game;

	game.start();


	return 1;
}