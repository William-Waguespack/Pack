#pragma once
#include "Core.h"
#include "Pack/Events/Event.h"
#include "Pack/Window.h"
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

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& GetApplication() { return *s_Instance; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};


	//To be defined in by a Client
	Application* CreateApplication();

}


