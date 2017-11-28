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

public:
    ~Game()
    {
        delete layer;
    };

    void init() override
    {

        window = createWindow("AdunGL Test Game", 960, 540);

        FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

        shader = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic120.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic120.frag");

        layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

        sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("/Users/adun/Desktop/AdunGL/asset/tb.png"));

        layer->add(sprite);

        fps = new Label("", -15.5f, 7.8f, "arial", maths::vec4(0, 1, 1, 1));

        layer->add(fps);
    }

    void tick() override // 1초 마다 실행
    {
        fps->text = std::to_string(getFPS()) + " fps";
        //std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
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

