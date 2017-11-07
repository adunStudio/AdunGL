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

Shader* shader;
Buffer* vbo;
IndexBuffer* ibo;
VertexArray* vao;


int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    printf("Supported OpenGL version is %s.\n", window.getVersion());
    printf("Supported GLSL version is %s.\n", window.getGLSLVersion());

#if 0
    GLfloat vertices[] =
            {
                    0, 0, 0,
                    8, 0, 0,
                    0, 3 , 0,
                    0, 3 , 0,
                    8, 3 , 0,
                    8, 0 , 0
            };

    GLuint vbo;

    // 버퍼 생성
    // void glGenBuffers(GLsizei n, GLuint* buffers)
    // glGenBuffers([생성할 버퍼 개수 integer], [버퍼 변수 array of GLuint])
    glGenBuffers(1, &vbo);

    // 버퍼 바인드
    // void glBindBuffer(GLenum target, GLuint buffer)
    // GL_ARRAY_BUFFER -> 꼭지점 값이 들어간다는 것을 의미
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 바인드된 버퍼에 데이터를 넣는다.
    // void glBufferData( GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
    // GL_STATIC_DRAW -> 데이터가 변경되지 않는다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 꼭짓점 값을 읽을때 어떻게 프로그래램에서 읽어야 하는지 정의해준다.
    // void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
    // index -> 꼭지점 데이터 배열의 인덱
    // size -> 꼭지점에서 사용하는 파라미터 개수
    // normalize-> 데이터에 대해서 정규화를 할지에 대한 결정을 하는 것이다. 데이터의 범위를 [-1, 1]로 변경을 하는 것
    // stride, pointer -> offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // 저장된 꼭지점(Vertex)을 사용가능하게 하는 것이다.
    // void glEnableVertexAttribArray(GLuint index) & void glDisableVertexAttribArray(GLuint index)
    glEnableVertexAttribArray(0);

    /*
    1. glGen* 함수를 통해서 값을 생성하고

    2. glBind* 함수를 통해서 변수에 Binding을 하고,

    3. glBufferData 함수로 값을 저장하고,

    4. Display에 대한 Callback을 받았을 때, glEnableVertexAttibArray() 함수를 통해 사용할 배열을 활성화시키고,

    5. glVertexAttribPointer()함수를 통해 값을 어떻게 읽을지에 대해서 파라미터 지정을 하고,

    6. 마지막으로 glDrawArray()함수를 통해 그리고 glDisableVertexAttribArray()함수를 통해 배열을 비활성화 시킨다.
    */



#else

    GLfloat vertices[] =
            {
                    0, 0, 0,
                    0, 3, 0,
                    8, 0, 0,
                    0, 3, 0
            };

    GLushort indices[] =
            {
                    0, 1, 2,
                    2, 3, 0

            };
    vbo = new Buffer(vertices, 4 * 3, 3);
    ibo = new IndexBuffer(indices, 6);

    vao->addBuffer(vbo, 0);


#endif

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    shader = new Shader("/Users/adun/Desktop/AdunGL/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/shaders/basic.frag");
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    //shader.setUniformMat4("ml_matrix", mat4::rotation(45.0f, vec3(0, 0, 1)));
    shader->setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));
    shader->setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));


    window.update(update);

    window.render([]() {
        Window::instance().clear();
#if 0
        // glEnableVertexAttribArray함수에서 지정한 꼭지점 배열을 활용하여 draw한다.
        // void glDrawArrays(GLenum mode, GLint first, GLsizei count)
        // mode -> 그려지는 도형
        // count -> 읽어들일 개수
        glDrawArrays(GL_TRIANGLES, 0, 6);
#else
        //vao->bind();
        ibo->bind();
        glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);
        ibo->bind();
        vao->unbind();
#endif

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
