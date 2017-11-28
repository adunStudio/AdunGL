#include <iostream>
#include <vector>
#include "AdunGL-Core/Adun.h"


class Game : public Adun
{
private:
    Window* window;
    Layer*  layer;
    Label*  fps;
    Sprite* sprite;
    Shader* shader;
    Mask*   mask;

public:
    ~Game()
    {
        delete layer;
    };

    void init() override
    {


        window = createWindow("AdunGL Test Game", 960, 540);

        FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

        shader = ShaderFactory::DefaultShader();

        layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

        TextureManager::add(new Texture("Basic", "/Users/adun/Desktop/AdunGL/asset/tb.png"));

        sprite = new Sprite(0, 0, 8, 4, TextureManager::get("Basic"));

        layer->add(sprite);

        fps = new Label("", -15.5f, 7.8f, "arial", maths::vec4(0, 1, 1, 1));

        layer->add(fps);

        Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
        mask = new Mask(new Texture("Mask", "/Users/adun/Desktop/AdunGL/asset/mask.png"));

        //layer->setMask(mask);

    }

    void tick() override // 1초 마다 실행
    {
        fps->text = std::to_string(getFPS()) + " fps";
        ADUNGL_INFO("%d ups, %d fps", getUPS(), getFPS());
    }

    void update() override // frame마다 실행
    {
        float speed = 0.5f;

        if(window->isKeyPressed('a'))
            sprite->position.x -= speed;
        if(window->isKeyPressed('d'))
            sprite->position.x += speed;
        if(window->isKeyPressed('w'))
            sprite->position.y += speed;
        if(window->isKeyPressed('s'))
            sprite->position.y -= speed;

        if(window->isKeyPressed('q'))
            exit(0);

        vec2 mouse = window->getMousePosition();
        shader->enable();
        shader->setUniform2f("light_pos", vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));

        static maths::vec3 scale(1.777778f, 1, 1);

        if(window->isKeyPressed("up"))
        {
            scale.x += speed * 1.777778f;
            scale.y += speed;
        }
        if(window->isKeyPressed("down"))
        {
            scale.x -= speed * 1.777778f;
            scale.y -= speed;
        }

        mask->transform = maths::mat4::scale(scale);
    }


    void render() override
    {
        layer->render();
    }
};


int main()
{
    Game game;

    game.start();


    return 1;
}

