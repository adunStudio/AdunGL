//
// Created by adun on 2017. 11. 6..
//

#include "camera.h"

namespace AdunGL
{
    namespace graphics
    {
        Camera* Camera::instance_ = nullptr;

        void Camera::rotateX(float angle)
        {
            instance_->rotate_x += angle;
        }

        void Camera::rotateY(float angle)
        {
            instance_->rotate_y += angle;
        }

        void Camera::rotateZ(float angle)
        {
            instance_->rotate_z += angle;
        }

        void Camera::transX(float d)
        {
            instance_->trans_x += d;
        }

        void Camera::transY(float d)
        {
            instance_->trans_y += d;
        }

        void Camera::transZ(float d)
        {
            instance_->trans_z += d;
        }

        float Camera::getRotateZ()
        {
            return instance_->rotate_z;
        }


        void Camera::reset()
        {
            instance_->rotate_x = instance_->rotate_y = instance_->rotate_z =
            instance_->trans_x = instance_->trans_y = instance_->trans_z = 0;
        }

        void Camera::inCamera()
        {
            glTranslatef(instance_->trans_x, instance_->trans_y, instance_->trans_z);

            glRotated(instance_->rotate_x, 1, 0, 0) ;
            glRotated(instance_->rotate_y, 0, 1, 0);
            glRotated(instance_->rotate_z, 0, 0, 1);
        }

        void Camera::drawAxis()
        {
            // x축 선
            glColor4f(1, 0, 0, 1.0);
            glBegin(GL_LINES);
            glVertex3f(0      ,  0     , 0);
            glVertex3f(0 + 30 ,  0     , 0);
            glEnd();

            // y축 선
            glColor4f(0, 1, 0, 1.0);
            glBegin(GL_LINES);
            glVertex3f(0    ,  0      , 0);
            glVertex3f(0     ,  0+ 30 , 0);
            glEnd();

            // z축 선
            glColor4f(0, 0, 1, 1.0);
            glBegin(GL_LINES);
            glVertex3f(0     ,  0      , 0 );
            glVertex3f(0     ,  0      , 0 + 30);
            glEnd();
        }
    }
}