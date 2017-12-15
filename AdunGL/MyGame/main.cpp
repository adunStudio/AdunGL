#include <iostream>
#include <vector>
#include "../AdunGL-Core/Adun.h"

#define WIDTH 1280
#define HEIGHT 720

class Game : public Adun
{
private:
	Window* window;
	Layer*  layer;
	Label*  fps;
	Sprite* sprite;
	Shader* shader;
	Mask*   mask;
	Label* debugInfo;

public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	};

	void init() override
	{
		window = createWindow("AdunGL Test Game", 1280, 720);

		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		
		shader = ShaderFactory::DefaultShader();
		
		layer = new Layer(new BatchRenderer2D(maths::tvec2<GLuint>(1280, 720)), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		TextureManager::add(new Texture("Basic", "MyGame/Asset/images/tb.png"));

		sprite = new Sprite(0, 0, 8, 4, TextureManager::get("Basic"));
		layer->add(sprite);

		fps = new Label("", -15.5f, 7.8f, maths::vec4(0, 1, 1, 1));
		layer->add(fps);

		debugInfo = new Label("", -15.5f, 6.8f, "arial", maths::vec4(1, 1, 0, 1));
		layer->add(debugInfo);

		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		mask = new Mask(new Texture("Mask", "MyGame/Asset/images/mask.png"));

		layer->setMask(mask);
		

	}

	void tick() override // 1초 마다 실행
	{
		fps->text = std::to_string(getFPS()) + " fps";
		ADUNGL_INFO("%d ups, %d fps", getUPS(), getFPS());
	}

	void update() override // frame마다 실행
	{
		if (window->isKeyPressed('z'))
		{
			((BatchRenderer2D*)layer->renderer)->setRenderTarget(RenderTarget::SCREEN);
		}
		if (window->isKeyPressed('Z'))
		{
			((BatchRenderer2D*)layer->renderer)->setRenderTarget(RenderTarget::BUFFER);
		}
		
	
		maths::tvec2<GLuint> size = ((BatchRenderer2D*)layer->renderer)->getViewportSize();


		if (window->isKeyPressed("up"))
		{
			size.x++;
			size.y++;
		}
		if (window->isKeyPressed("down"))
		{
			size.x--;
			size.y--;
		}

		debugInfo->text = std::to_string(size.x) + ", " + std::to_string(size.y);
		((BatchRenderer2D*)layer->renderer)->setViewportSize(size);
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