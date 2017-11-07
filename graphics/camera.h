//
// Created by adun on 2017. 11. 6..
//

#ifndef ADUNGL_CAMERA_H
#define ADUNGL_CAMERA_H

#include <cassert>
#include <GLUT/glut.h>

namespace AdunGL
{
    namespace graphics
    {
        class Camera
        {
        private:
            static Camera* instance_;

        public:
            static Camera& instance()
            {
                if(!instance_)
                {
                    instance_ = new Camera();
                }

                return *instance_;
            }

            static void rotateX(float angle);
            static void rotateY(float angle);
            static void rotateZ(float angle);

            static void transX(float d);
            static void transY(float d);
            static void transZ(float d);

            static void reset();

            static void inCamera();

            static void drawAxis();

        private:
            Camera() = default;

            float rotate_x = 0;
            float rotate_y = 0;
            float rotate_z = 0;

            float trans_x = 0;
            float trans_y = 0;
            float trans_z = 0;
        };
    }
}
#endif //ADUNGL_CAMERA_H
