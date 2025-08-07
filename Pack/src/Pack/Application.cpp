#include "Packpch.h"
#include "Application.h"

#include "Pack/Log.h"

#include <glad/glad.h>

#include "Input.h"



namespace Pack
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PACK_CORE_ASSERT(!s_Instance, "Application Already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		

		uint32_t indicies[] =
		{
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0)  in vec3 a_Position;

			out vec3 FragPos;
			
			void main()
			{
				FragPos = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core

			out vec4 color;
			in vec3 FragPos;
			
			void main()
			{
				color = vec4(FragPos * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader = std::make_unique<Shader>(vertexSrc, fragSrc);
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));

		//PACK_CORE_TRACE("{0}, {1}", event, "FROM APPLICATION");

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.getHandled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	Application::~Application()
	{

	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			auto [x, y] = Input::GetMousePosition();
			//PACK_CORE_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}
}