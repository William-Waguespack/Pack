#include <Pack.h>

class ExampleLayer : public Pack::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	inline void OnUpdate() override
	{
		PACK_INFO("ExampleLayer::Update");
	}

	inline void OnEvent(Pack::Event& event) override
	{
		PACK_TRACE("{0}", event);
	}

};

class Sandbox : public Pack::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Pack::Application* Pack::CreateApplication()
{
	return new Sandbox();
}