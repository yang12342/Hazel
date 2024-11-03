#pragma once

#include "Core.h"


#include	"Hazel/Events/Event.h"
#include	"Hazel/Events/ApplicationEvent.h"
#include	"LayerStack.h"
#include	"Window.h"


#include "Hazel/ImGui/ImGuiLayer.h"


namespace Hazel
{
	class HAZEL_API Application
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



		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	//to be define in client
	Application* CreateApplication();
};

