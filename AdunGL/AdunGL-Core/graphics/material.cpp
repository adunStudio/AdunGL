#include "material.h"

namespace AdunGL
{
	namespace graphics
	{
		Material::Material(Shader* shader)
			: m_shader(shader)
		{
			initUniformStorage();
		}

		Material::~Material()
		{
			delete m_shader;
		}

		void Material::initUniformStorage()
		{
			m_uniformDataSize = 0;

			const std::vector<ShaderUniformDeclaration*>& uniforms = m_shader->getUniformDeclarations();;

			for (ShaderUniformDeclaration* uniform : uniforms)
				m_uniformDataSize += uniform->getSize();

			m_uniformData = new unsigned char[m_uniformDataSize];

			memset(m_uniformData, 0, m_uniformDataSize);
		}

		const ShaderUniformDeclaration* Material::getUniformDeclaration(const string& name) const
		{
			for (ShaderUniformDeclaration* uniform : m_shader->getUniformDeclarations())
			{
				if (uniform->getName() == name)
					return uniform;
			}

			return nullptr;
		}

		void Material::dumpUniformData() const
		{
			const vector<ShaderUniformDeclaration*>& uniforms = m_shader->getUniformDeclarations();

			for (int i = 0; i < uniforms.size(); ++i)
			{
				ShaderUniformDeclaration* declaration = uniforms[i];

				switch (declaration->getType())
				{
				case ShaderUniformDeclaration::Type::MAT4:
					cout << "umpUniformData() : MAT4" << endl;
					break;
				}
			}
		}

		void Material::bind() const
		{
			m_shader->enable();
			m_shader->resolveAndSetUniforms(m_uniformData, m_uniformDataSize);
		}

		void Material::unbind() const
		{
			m_shader->disable();
		}

		MaterialInstance::MaterialInstance(Material* material)
			: m_material(material), m_setUniforms(0)
		{
			initUniformStorage();
		}

		void MaterialInstance::initUniformStorage()
		{
			m_uniformDataSize = 0;

			const std::vector<ShaderUniformDeclaration*>& uniforms = m_material->m_shader->getUniformDeclarations();
		
			for (ShaderUniformDeclaration* uniform : uniforms)
				m_uniformDataSize += uniform->getSize();

			m_uniformData = new unsigned char[m_uniformDataSize];

			memset(m_uniformData, 0, m_uniformDataSize);
		}
		
		int MaterialInstance::getUniformDeclarationIndex(const string& name) const
		{
			vector<ShaderUniformDeclaration*> uniforms = m_material->m_shader->getUniformDeclarations();
			
			for (GLuint i = 0; i < uniforms.size(); ++i)
			{
				if (uniforms[i]->getName() == name)
					return i;
			}

			return -1;
		}

		void MaterialInstance::unsetUniform(const string& name)
		{
			// TODO: 코드 이해 불가 // 공부 필요
			int index = getUniformDeclarationIndex(name);
			GLuint mask = !(1 << index);
			
			m_setUniforms &= mask;
		}

		void MaterialInstance::bind() const
		{
			m_material->bind();

			GLuint overrides = m_setUniforms;
			GLuint index = 0;

			while (overrides > 0)
			{
				if (overrides & 1)
					m_material->m_shader->resolveAndSetUniform(index, m_uniformData);
			
				overrides >>= 1;
				index++;
			}
		}

		void MaterialInstance::unbind() const
		{
			m_material->unbind();
		}
	}
}