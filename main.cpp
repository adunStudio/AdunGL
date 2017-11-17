#include <iostream>
#include <GLUT/glut.h>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/maths.h"
#include "utils/fileutils.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

void update();
void render();

Shader* shader;
Buffer* vbo;
IndexBuffer* ibo;
VertexArray* vao, *sprite1, *sprite2;



int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    printf("Supported OpenGL version is %s.\n", window.getVersion());
    printf("Supported GLSL version is %s.\n", window.getGLSLVersion());

    GLfloat vertices[] =
            {
                    0, 0, 0,    // 좌 하단
                    0, 3, 0,    // 좌 상단
                    8, 3, 0,    // 우 상단
                    8, 0, 0     // 우 하단
            };

    GLushort indices[] =
            {
                    0, 1, 2,
                    2, 3, 0

            };

    GLfloat colorsA[] = {
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1,
            1, 0, 1, 1,
    };

    GLfloat colorsB[] = {
            0.2, 0.3, 0.8, 1,
            0.2, 0.3, 0.8, 1,
            0.2, 0.3, 0.8, 1,
            0.2, 0.3, 0.8, 1,
    };

    vao = new VertexArray();
    sprite1 = new VertexArray();
    sprite2 = new VertexArray();

    //vbo = new Buffer(vertices, 4 * 3, 3);
    ibo = new IndexBuffer(indices, 6);

    sprite1->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    sprite1->addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);
    sprite2->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    sprite2->addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);



    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    shader = new Shader("/Users/adun/Desktop/AdunGL/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/shaders/basic.frag");
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    //shader.setUniformMat4("ml_matrix", mat4::rotation(45.0f, vec3(0, 0, 1)));
    shader->setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));
   // shader->setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));


    window.update(update);

    // void glEnableClientState(GLenum 배열)
    // OpenGL 버텍스 배열로 사용될 배열 타입을 사용 가능 또는 불가능하도록 설정한다.
    // 지오메트리 정의에 사용될 벌텍스 배열을 지정할 것인지 그렇지 않을 것인지를 OpenGL에 알리는 역할을 한다.
    glEnableClientState(GL_VERTEX_ARRAY);

    window.render([]() {
        Window::instance().clear();

        render();

        glutSwapBuffers();
    });

    window.run();
    return 1;
}

void update()
{
    int x, y;
    Window::instance().getMousePosition(x, y);
    shader->setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.f)));
    glutPostRedisplay();
}

void render()
{

    // 배열 데이터로부터 기본 모델을 렌더링한다 배열에는 인덱스가 적용되며 유효한 인덱스값의 범위 또한 지정된다
    // 배열 데이터를 순차적으로 읽는 것이 아니라 인덱스 배열을 순차적으로 읽는 함수이다.
    // 인덱스 배열은 단순히 버텍스 데이터가 나열된 순서대로 읽어들이지 않으며, 공유 버텍스 데이터 활용을 위해 중보되는 경우도 있다
    // void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
    // 모드, 시작, 끝, 개수, 타입, 포인터
    // GLsizei: 배열 내에 있는 좌표 사이의 바이트 간격
    //    type: 인덱스 배열에 사용되는 데이터 타입
    // GLvoid*: 인덱스 배열의 위치를 지정하는 포인터

    sprite1->bind();
    ibo->bind();
    shader->setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
    glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);
    ibo->unbind();
    sprite1->unbind();

    sprite2->bind();
    ibo->bind();
    shader->setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
    glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);
    ibo->unbind();
    sprite2->unbind();

    // 버텍스 배열로부터 순차적인 기본 모델을 만들어낸다.
    // 설정된 버텍스 배열의 내용을 사용하여 일련의 기본 모델들을 그리는 데 사용되는 함수이다.
    // 기본 모델의 타입을 받아 지정된 범위의 모든 버텍스를 사용할 떄까지 드로잉이 계속된다.
    // GLenum: 드로잉할 기본 모델의 종류
    //  GLint: 배열의 첫 번재 인덱스
    // GLsizei: 사용할 인덱스의 수
    // glDrawArrays(GL_TRIANGLES, 0, 12);

}

