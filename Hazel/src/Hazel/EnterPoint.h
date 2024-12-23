#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int  main(int argc,char** argv)
{
	Hazel::Log::Init();
	::Hazel::Log::GetCoreLogger()->warn("Initialized Log");
	int a = 5;
	HZ_INFO("Hello! Var={0}", a);


	printf("Hello Engine!");
	auto app = Hazel::CreateApplication();
 	app->Run();
	delete app;

}

#endif