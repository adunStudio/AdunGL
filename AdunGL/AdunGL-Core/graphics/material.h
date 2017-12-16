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
			friend class MaterialInstance;

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
			GLuint m_uniformDataSize;
			GLuint m_setUniforms;

		public:
			MaterialInstance(Material* material);
			
			inline Material* getMaterial() const { return m_material; }

			void bind() const;
			void unbind() const;
			void unsetUniform(const string& name);

			template<typename T>
			void setUniform(const string& name, const T& value)
			{
				int index = getUniformDeclarationIndex(name);
				if (index == -1)
				{
					ADUNGL_ERROR("Could not find uniform %s", name.c_str());
					return;
				}
				ShaderUniformDeclaration* uniform = m_material->m_shader->getUniformDeclarations()[index];
				memcpy(m_uniformData + uniform->getOffset(), &value, uniform->getSize());

				m_setUniforms |= 1 << index;
			}

			template<> void setUniform<float>(const string& name, const float& value) {}

		private:
			void initUniformStorage();
			int getUniformDeclarationIndex(const string& name) const;

		};
	}
}