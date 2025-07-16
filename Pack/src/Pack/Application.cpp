#include "Application.h"
#include "Pack/Events/ApplicationEvent.h"
#include "Pack/Log.h"



namespace Pack
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		PACK_TRACE(e);


		while (true)
		{

		}
	}
}