#pragma once
#include "Core.h"


namespace Pack
{
	//dll code
	class PACK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};


	//To be defined in by a Client
	Application* CreateApplication();
}


