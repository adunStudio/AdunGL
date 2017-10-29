#include <iostream>
#include "graphics/window.h"
#include "maths/maths.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;

Vec2 v1(1.0f, 20.f);
Vec2 v2(2.0f, 1.0f);
Vec2 v3(3.0f, 21.0f);

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    cout << "OpenGL Version: " << window.getVersion() << endl;

    cout << "window width: " << window.getWidth()  << endl;
    cout << "window height:" << window.getHeight() << endl;

    v1 +=  v2;

    window.update([]() {

        cout << v1 << endl;
        cout << (v1 == v3) << endl;

        if(Window::isKeyPressed('a'))
            cout << "a키 눌림" << endl;

        if(Window::isMouseButtonPressed(GLUT_LEFT_BUTTON))
            cout << "왼쪽 키 눌림" << endl;

        int x, y;
        Window::getMousePosition(x, y);

        //cout << x << " : " << y << endl;
    });

    window.render([]() {

        Window::instance().clear();

        glBegin(GL_TRIANGLES);
        {
            glVertex2f(-0.5, -0.5);
            glVertex2f(-0.0, 0.5);
            glVertex2f(0.5, -0.5);
        }
        glEnd();

        glutSwapBuffers();
    });

    window.run();

    return 1;
}
