#include "Test3D.h"

Test3D::Test3D()
	: Layer3D(new Scene())
{
	m_rotation = 0.0f;
	m_setUniforms[0] = true;
	m_setUniforms[1] = true;



}

Test3D::~Test3D()
{
}

void Test3D::onInit(Renderer3D& renderer, Scene& scene)
{
	VertexArray* va = MeshFactory::createQuad(0, 0, 5, 5);
	IndexBuffer* ib = new IndexBuffer(new GLuint[6]{ 0, 1, 2, 2, 3, 0 }, 6);

	Material* material = new Material(Shader::FromFile("Scene", "MyGame/Shaders/scene.shader"));
	
	material->setUniform("pr_matrix", mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	material->setUniform("vw_matrix", mat4::Translate(vec3(0, 0, -10.0f)));
	material->setUniform("ml_matrix", mat4::Rotate(45.0f, vec3(0, 1, 0)));

	m_cubeMaterial   = new MaterialInstance(material);
	m_sphereMaterial = new MaterialInstance(material);

	Model* cube   = new Model("MyGame/Asset/Objs/cube.obj"  , m_cubeMaterial);
	Model* sphere = new Model("MyGame/Asset/Objs/sphere.obj", m_sphereMaterial);

	m_scene->add(cube->getMesh());
	m_scene->add(sphere->getMesh());

}

void Test3D::onTick()
{
	Adun& Ad = Adun::getAdun();
	//ADUNGL_INFO("%d ups, %d fps", Ad.getUPS(), Ad.getFPS());

	// m_Cube->GetMaterialInstance()->GetMaterial()->DumpUniformData();
}


void Test3D::onUpdate()
{
	mat4 transform = mat4::Rotate(m_rotation, vec3(1, 0, 0)) * mat4::Rotate(m_rotation, vec3(0, 1, 0)) * mat4::Rotate(m_rotation, vec3(0, 0, 1));

	m_rotation += 0.5;

	if(m_setUniforms[0])
		m_cubeMaterial->setUniform("ml_matrix", mat4::Translate(vec3(-4, 0, 0))  * (transform) *mat4::Scale(vec3(1.4f, 1.4f, 1.4f)));
	if (m_setUniforms[1])
		m_sphereMaterial->setUniform("ml_matrix", mat4::Translate(vec3(4, 0, 0)) *transform);
}

bool Test3D::onEvent(const Event& event)
{
	return false;
}