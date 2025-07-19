#pragma once
#include "Core.h"
#include "Pack/Events/Event.h"
#include "Pack/Windows/Window.h"
#include "Pack/Events/ApplicationEvent.h"
#include "Pack/LayerStack.h"

namespace Pack
{
	//dll code
	class PACK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};


	//To be defined in by a Client
	Application* CreateApplication();

}


