#pragma once

#ifdef PACK_PLATFORM_WINDOWS

//dll code
extern Pack::Application* Pack::CreateApplication();

int main()
{
	Pack::Application* app = Pack::CreateApplication();
	app->Run();
	delete app;


	return 0;
}

#endif