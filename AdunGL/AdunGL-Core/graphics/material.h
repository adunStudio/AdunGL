#pragma once

#include <map>
#include <GL/freeglut.h>
#include "shaders/shader.h"
#include "../utils/log.h"

namespace AdunGL
{
	namespace graphics
	{
		class Material
		{
		private:
			Shader* m_shader;
			unsigned char* m_uniformData;
			unsigned int m_uniformDataSize;

		public:
			Material(Shader* shader);
			~Material();

			void bind() const;
			void unbind() const;
			void dumpUniformData() const;

			template<typename T>
			void setUniform(const string& name, const T& value)
			{
				const ShaderUniformDeclaration* uniform = getUniformDeclaration(name);
				if (!uniform)
				{
					ADUNGL_ERROR("Could not find uniform %s !", name);
					return;
				}
				memcpy(m_uniformData + uniform->getOffset(), &value, uniform->getSize());
			}

			template<typename T>
			const T* getUniform(const string& name) const
			{
				return getUniform<T>(getUniformDeclaration(name));
			}

			template<typename T>
			const T* getUniform(const ShaderUniformDeclaration* uniform) const
			{
				return (T*)&m_uniformData[uniform->getOffset()];
			}

		private:
			void initUniformStorage();
			const ShaderUniformDeclaration* getUniformDeclaration(const string& name) const;
		};

		class MaterialInstance
		{
		private:
			Material* m_material;
			unsigned char* m_uniformData;

		public:
			MaterialInstance(Material* material);
			
			inline Material* getMaterial() const { return m_material; }

			void bind() const;
			void unbind() const;

			template<typename T>
			void setUniform(const string& name, const T& value)
			{
				AdunGL_ERROR("Unknown type");
			}

			template<> void setUniform<float>(const string& name, const float& value) {}

		private:
			void initUniformStorage();

		};
	}
}