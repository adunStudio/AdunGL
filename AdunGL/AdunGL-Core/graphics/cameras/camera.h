#pragma once

#include "../../maths/maths.h"

namespace AdunGL
{
	namespace graphics
	{
		using namespace maths;

		class Camera
		{
		protected:
			mat4 m_projectionMatrix, m_viewMatrix;
			vec3 m_position, m_rotation, m_focalPoint;

		public:
			Camera(const mat4& projectionMatrix);

			virtual void update()
			{
			}

			// 인라인의 향연
			// get set
			inline const vec3& GetPosition() const { return m_position;  }
			inline void SetPosition(vec3& position) { m_position = position; }

			inline const vec3& GetRotation() const { return m_rotation;  }
			inline void SetRotation(const vec3& rotation) { m_rotation = rotation; }

			inline const maths::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
			inline void SetProjectionMatrix(const mat4& projectionMatrix) { m_projectionMatrix = projectionMatrix; }

			inline void Translate(const vec3& translation) { m_position += translation; }
			inline void Rotate(const vec3& rotation) { m_rotation += rotation; }

			inline void Translate(float x, float y, float z) { m_position += vec3(x, y, z); }
			inline void Rotate(float x, float y, float z) { m_rotation += vec3(x, y, z); }
			
			inline const vec3& GetFocalPoint() const { return m_focalPoint; }
			
			inline const mat4& GetViewMatrix() { return m_viewMatrix; }
		};
	}
}