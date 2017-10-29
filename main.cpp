#include <iostream>
#include "graphics/window.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    cout << "OpenGL Version: " << window.getVersion() << endl;

    cout << "window width: " << window.getWidth()  << endl;
    cout << "window height:" << window.getHeight() << endl;

    window.update([]() {

        if(Window::isKeyPressed('a'))
            cout << "a키 눌림" << endl;

        if(Window::isMouseButtonPressed(GLUT_LEFT_BUTTON))
            cout << "왼쪽 키 눌림" << endl;

        int x, y;
        Window::getMousePosition(x, y);

        cout << x << " : " << y << endl;
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
