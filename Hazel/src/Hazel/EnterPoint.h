#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int  main(int argc,char** argv)
{
	printf("Hello Engine!");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

}

#endif