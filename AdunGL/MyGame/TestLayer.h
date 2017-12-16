#pragma once

#include "../AdunGL-Core/Adun.h"

class TestLayer : public Layer2D
{
private:
	Label*  m_fps;
	Label** debugInfo;

public:
	TestLayer();
	~TestLayer();

	void onInit(Renderer2D& renderer, Shader& shader) override;
	void onTick() override;
	void onUpdate() override;
	bool onEvent(const Event& event) override;
	void onRender(Renderer2D& renderer) override;
};