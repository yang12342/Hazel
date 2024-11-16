#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include <glad/glad.h>
#include "Renderer/Renderer.h"

#include "Input.h"


namespace Hazel
{

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)


	Application* Application::s_Instance = nullptr;
	

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback([this](Event& event) {
			this->OnEvent(event);  // 调用成员函数
			});

		m_Window->SetVSync(true);
		//m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f,	0.8f,	0.2f,	0.8f,	1.0f,
			 0.5f, -0.5f, 0.0f,	0.2f,	0.3f,	0.8f,	1.0f,
			 0.0f, 0.5f,  0.0f,	0.8f,	0.8f,	0.2f,	1.0f
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA.reset(VertexArray::Create());

		float squarevertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,	0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squarevertices, sizeof(squarevertices)));

		BufferLayout squarelayout =
		{
			{ShaderDataType::Float3,"a_Position"}
		};
		squareVB->SetLayout(squarelayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareindices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);



		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0)in vec3 a_Position;
			layout(location=1)in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;			
			void main()
			{
				v_Position=a_Position;
				gl_Position=vec4(a_Position,1.0);
				v_Color=a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0)out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color=vec4(v_Position*0.5+0.5,1.0);
				color=v_Color;
			}
		)";

		std::string BlueShadervertexSrc = R"(
			#version 330 core
			
			layout(location=0)in vec3 a_Position;

			out vec3 v_Position;
			void main()
			{
				v_Position=a_Position;
				gl_Position=vec4(a_Position,1.0);
			}
		)";

		std::string BlueShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location=0)out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color=vec4(0.2, 0.3, 0.8,1.0);
			}
		)";


		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
		m_BlueShader.reset(new Shader(BlueShadervertexSrc, BlueShaderfragmentSrc));
	}


	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		HZ_CORE_INFO("{0}",e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{

		while (m_running)
		{
			RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}

