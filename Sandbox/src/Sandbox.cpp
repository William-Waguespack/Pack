#include <Pack.h>

#include "imgui/imgui.h"

class ExampleLayer : public Pack::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	inline void OnUpdate() override
	{
		//PACK_INFO("ExampleLayer::Update");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Text("Text Here");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::End();
	}

	inline void OnEvent(Pack::Event& event) override
	{
		//PACK_TRACE("{0}, {1}", event, " FROM SANDBOX");
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