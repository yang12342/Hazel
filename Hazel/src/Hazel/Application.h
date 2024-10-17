#pragma once

#include "Core.h"


#include	"Hazel/Events/Event.h"
#include	"Hazel/Events/ApplicationEvent.h"
#include	"LayerStack.h"
#include	"Window.h"


namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool Application::OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_running = true;
		LayerStack m_LayerStack;
	};

	//to be define in client
	Application* CreateApplication();
};

