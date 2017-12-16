#include "../AdunGL-Core/Adun.h"
#include "TestLayer.h"
#include "Test3D.h"

#define WIDTH  960
#define HEIGHT 540

class Game : public Adun
{
public:
	Game()
		: Adun("AdunGL Test Game", WIDTH, HEIGHT)
	{

	}

	~Game()
	{
	
	};

	void init() override
	{
		Adun::init();
		pushLayer(new TestLayer());
		pushLayer(new Test3D());

	}
};


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	Game game;

	game.start();


	return 1;
}