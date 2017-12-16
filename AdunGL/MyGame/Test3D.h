#pragma once

#include "../AdunGL-Core/Adun.h"

class Test3D : public Layer3D
{
private:
	MaterialInstance* m_cubeMaterial;
	MaterialInstance* m_sphereMaterial;

	float m_rotation;
	
	bool m_setUniforms[2];

public:
	Test3D();
	~Test3D();

	void onInit(Renderer3D& renderer, Scene& scene) override;
	
	void onTick() override;
	void onUpdate() override;
	bool onEvent(const Event& event) override;
};