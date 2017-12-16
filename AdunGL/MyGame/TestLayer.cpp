#include "TestLayer.h"

TestLayer::TestLayer()
	: Layer2D(ShaderFactory::DefaultShader(), mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TestLayer::~TestLayer()
{
	
}

void TestLayer::onInit(Renderer2D& renderer, Shader& shader)
{
	FontManager::get()->setScale(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
	renderer.setRenderTarget(RenderTarget::BUFFER);
	renderer.addPostEffectsPass(new PostEffectsPass(Shader::FromFile("Horizontal Blur", "MyGame/Shaders/postfx.shader")));
	renderer.setPostEffects(false);
	
	Texture::setFIlter(TextureFilter::NEARST);
	TextureManager::add(new Texture("Basic", "MyGame/Asset/images/tb.png"));
	add(new Sprite(0, 0, 8, 8, TextureManager::get("Basic")));
	add(new Sprite(-8.0f, -8.0f, 6, 6, maths::vec4(1, 1, 0, 0)));

	m_fps = new Label("", -15.5f, 7.8f, maths::vec4(0, 1, 1, 1));
	add(m_fps);

	debugInfo = new Label*[10];
	debugInfo[0] = new Label("", -15.5f, 6.8f, "arial", maths::vec4(1, 1, 0, 1));
	debugInfo[1] = new Label("", -15.5f, 5.8f, "arial", maths::vec4(1, 1, 0, 1));
	add(debugInfo[0]);
	add(debugInfo[1]);


	Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	Mask* mask = new Mask(new Texture("Mask", "MyGame/Asset/images/mask.png"));
	mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));
	//setMask(mask);
}

void TestLayer::onTick()
{
	Adun& Ad = Adun::getAdun();

	m_fps->text = std::to_string(Ad.getFPS()) + " fps";
	ADUNGL_INFO("%d ups, %d fps", Ad.getUPS(), Ad.getFPS());
}

void TestLayer::onUpdate()
{
}

bool TestLayer::onEvent(const Event& event)
{
	return false;
}

void TestLayer::onRender(Renderer2D& renderer)
{
	if (m_window->isKeyPressed('t'))
	{
		renderer.setRenderTarget(renderer.getRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);

	}
	if (m_window->isKeyPressed('p'))
	{
		renderer.setPostEffects(!renderer.getPostEffects());
	}

	debugInfo[0]->text = std::string("Target: ") + (renderer.getRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
	debugInfo[1]->text = std::string("PostFX: ") + (renderer.getPostEffects() ? "On" : "Off");
}


