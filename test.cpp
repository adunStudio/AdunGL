#include <GL/glut.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);

int Langle = 0;
int Rangle = 0;

struct camera
{
    int xrot = 0;
    int yrot = 0;
    int zrot = 0;
    int tx = 0;
    int ty = 0;
    int tz = 0;
};

camera c;

struct Torus
{
    int height;
    int spin;
    int tx;
    int ty = 250;

};

struct list
{
    Torus T[10];
    int top = 0;
}list;


// 윈도우 출력 함수


void Torus_move()
{
    list.T[list.top].tx = 20;
    list.T[list.top].ty -= 2;
    list.T[list.top].spin += 10;
    if (list.T[list.top].ty < list.T[list.top].height)
    {
        list.T[list.top].tx = 0;
        list.T[list.top].spin = 0;
        list.T[list.top].ty=list.T[list.top].height;
        list.top++;
        if (list.top == 10)
        {
            list.top = 0;
            list.T[list.top].ty = 250;
        }
    }
}


void TimerFunction(int value)
{

    glutPostRedisplay();
    glutTimerFunc(50, TimerFunction, 1);

}
void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {


    }

}
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {

        case'X':
            c.xrot += 10;
            break;
        case'x':
            c.xrot -= 10;
            break;
        case'Y':
            c.yrot += 10;
            break;
        case'y':
            c.yrot -= 10;
            break;
        case'Z':
            c.zrot += 10;
            break;
        case'z':
            c.zrot -= 10;
            break;
        case'w':
            c.ty += 10;
            break;
        case's':
            c.ty -= 10;
            break;
        case'a':
            c.tx -= 10;
            break;
        case'd':
            c.tx += 10;
            break;
        case'+':
            c.tz -= 10;
            break;
        case'-':
            c.tz += 10;
            break;
        case'i':
            c.xrot = 0; c.yrot = 0; c.zrot = 0;
            c.tx = 0; c.ty = 0; c.tz = 0;
        default:
            break;
    }

}




GLvoid drawScene(GLvoid)
{
    //glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    gluLookAt(0, 1, 1,
              0.0, 0.0, -1.0,
              0.0, 1.0, 0.0);

    glPushMatrix();

    glTranslatef(c.tx, c.ty, c.tz);
    glRotatef(c.xrot, 1, 0, 0);
    glRotatef(c.yrot, 0, 1, 0);
    glRotatef(c.zrot, 0, 0, 1);

    glPushMatrix();//밑바닥
    {
        glColor3f(0.5, 0.5, 0);
        glTranslatef(0, -10, 0);
        glRotatef(90, 1, 0, 0);

        glRectf(-200, -200, 200, 200);
    }
    glPopMatrix();

    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex2i(0, 0);
    glVertex2i(0, 300);

    glEnd();
    Torus_move();
    for (int i = 0; i < list.top+1; i++)
    {
        list.T[i].height = (15 * (i));

        glPushMatrix();//밑닥
        {
            glColor3f(0, 1, 0.5);

            glRotatef(list.T[i].spin, 0, 1, 0);
            glTranslatef(list.T[i].tx, list.T[i].ty, 0);
            glRotatef(90, 1, 0, 0);
            glutWireTorus(10, 35, 10, 25);
        }
        glPopMatrix();
    }


    glPopMatrix();
    glutSwapBuffers();; // 화면에 출력하기
}


GLvoid Reshape(int w, int h)
{
    // 뷰포트 변환 설정: 출력 화면 결정
    glViewport(0, 0, w, h);
    // 클리핑 변환 설정: 출력하고자 하는 공간 결정
    // 아래 3줄은 투영을 설정하는 함수
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 원근 투영을 사용하는 경우:
    gluPerspective(60.0, 1.0, 1.0, 1000.0);
    glTranslatef(0.0, 0.0, -500.0);
    // glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
    // 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
    glMatrixMode(GL_MODELVIEW);
    // 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)

}
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Example2");
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(50, TimerFunction, 1);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape); glutMainLoop();
    return 1;
}