#pragma once

#ifdef PACK_PLATFORM_WINDOWS

//dll code
extern Pack::Application* Pack::CreateApplication();

int main()
{
	Pack::Log::Init();

	PACK_CORE_WARN("Initialized Log!");
	int a = 5;
	PACK_CORE_INFO("Hello! Var = {0}", a);

	Pack::Application* app = Pack::CreateApplication();
	app->Run();
	delete app;


	return 0;
}

#endif