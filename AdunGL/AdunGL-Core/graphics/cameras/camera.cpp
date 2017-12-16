#include "camera.h"

namespace AdunGL
{
	namespace graphics
	{
		Camera::Camera(const mat4&  projectionMatrix)
			: m_projectionMatrix(projectionMatrix)
		{
			m_viewMatrix = mat4::Identity();
			m_position = vec3();
			m_rotation = vec3();
		}
	}
}