#pragma once

#include "../AdunGL-Core/Adun.h"

class Test3D : public Layer3D
{
private:
	Mesh* m_cube;
	Material* m_material;

	float m_rotation;

public:
	Test3D();
	~Test3D();

	void onInit(Renderer3D& renderer, Scene& scene) override;
	
	void onTick() override;
	void onUpdate() override;
	bool onEvent(const Event& event) override;
};