#pragma once

#include "Core.h"

#include	"Window.h"
#include	"LayerStack.h"
#include	"Hazel/Events/Event.h"
#include	"Hazel/Events/ApplicationEvent.h"

#include "Hazel/Core/Timestep.h"

#include	"Hazel/ImGui/ImGuiLayer.h"



namespace Hazel
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		inline static Application& Get()
		{
			return *s_Instance;
		}
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool Application::OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running = true;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;



	private:
		static Application* s_Instance;
	};

	//to be define in client
	Application* CreateApplication();
};

