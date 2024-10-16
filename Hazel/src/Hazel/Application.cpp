#include "hzpch.h"
#include "Application.h"


#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel
{

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		HZ_CORE_INFO("{0}",e);
	}

	void Application::Run()
	{

		while (m_running)
		{
			m_Window->OnUpdate();
		}
	}
}