#include <iostream>
#include "graphics/window.h"
#include "maths/maths.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;

Vec2 v2(1.0f, 20.f);
Vec3 v3(2.0f, 1.0f, 3.0f);
Vec4 v4(3.0f, 21.0f, 4.3f, 34.3f);

Matrix4 position = Matrix4::perspective(1, 1, 1, 1);

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    position *= Matrix4::identity();

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

        //cout << x << " : " << y << endl;
    });

    window.render([]() {

        //cout << v2 << endl;
        //cout << v3 << endl;
        //cout << v4 << endl;

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
