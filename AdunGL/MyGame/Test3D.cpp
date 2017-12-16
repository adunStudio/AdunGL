#include "Test3D.h"

Test3D::Test3D()
	: Layer3D(new Scene())
{
	m_rotation = 0.0f;
}

Test3D::~Test3D()
{
}

void Test3D::onInit(Renderer3D& renderer, Scene& scene)
{
	VertexArray* va = MeshFactory::createQuad(0, 0, 5, 5);
	IndexBuffer* ib = new IndexBuffer(new GLuint[6]{ 0, 1, 2, 2, 3, 0 }, 6);

	m_material = new Material(Shader::FromFile("Scene", "MyGame/Shaders/scene.shader"));
	m_cube = MeshFactory::createCube(5.0f, new MaterialInstance(m_material));
	scene.add(m_cube);

	m_material->setUniform("pr_matrix", mat4::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	m_material->setUniform("vw_matrix", mat4::translation(vec3(0, 0, -10.0f)));
	m_material->setUniform("ml_matrix", mat4::rotation(45.0f, vec3(0, 1, 0)));
}

void Test3D::onTick()
{
	Adun& Ad = Adun::getAdun();
	ADUNGL_INFO("%d ups, %d fps", Ad.getUPS(), Ad.getFPS());

	// m_Cube->GetMaterialInstance()->GetMaterial()->DumpUniformData();
}

float g_Rotation = 0.0f;

void Test3D::onUpdate()
{
	mat4 transform = mat4::rotation(g_Rotation, vec3(1, 0, 0)) * mat4::rotation(g_Rotation, vec3(0, 1, 0)) * mat4::rotation(g_Rotation, vec3(0, 0, 1));
	m_material->setUniform("ml_matrix", transform);
	g_Rotation += 0.01f;
}

bool Test3D::onEvent(const Event& event)
{
	return false;
}