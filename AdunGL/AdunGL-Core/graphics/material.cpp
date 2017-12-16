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
			: m_material(material)
		{

		}
	}
}