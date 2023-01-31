#include <Hazel.h>
#include <imgui.h>
/* --EntryPoint.h
int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
*/

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("example")
	{
		float vertices[7 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 0.7f, 0.4f, 1.0f,

			 -0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.8f, 1.0f,
			  0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.2f, 1.0f,
			  0.5f,  0.5f, 0.0f, 0.2f, 0.8f, 0.1f, 1.0f,
			 -0.5f,  0.5f, 0.0f, 0.8f, 0.1f, 0.2f, 1.0f,
		};

		m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);

		unsigned int indices[] = { 0,1,2 };
		m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray.reset(Hazel::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_VertexArray->UnBind();

		unsigned int SquareIndices[] = { 3,4,5,5,6,3 };
		m_SquareIBO.reset(Hazel::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(unsigned int)));

		m_SquareVAO.reset(Hazel::VertexArray::Create());
		m_SquareVAO->AddVertexBuffer(m_VertexBuffer);
		m_SquareVAO->SetIndexBuffer(m_SquareIBO);
		m_SquareVAO->UnBind();

		std::string VertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			void main()
			{
				gl_Position = projection * view * model * vec4(a_Position, 1.0f);
				v_Color = a_Color;
			}
		)";

		std::string FragmentSource = R"(
			#version 330 core
			
			out vec4 color;
			in vec4 v_Color;
			void main()
			{
				
				color = v_Color;
			}

		)";
		std::string SquareFragmentSource = R"(
			#version 330 core
			out vec4 color;

			uniform vec3 u_Color;
			
			void main()
			{
				
				color = vec4(u_Color,1.0f);
			}

		)";

		m_Shader.reset(Hazel::Shader::CreateShader(VertexSource, FragmentSource));
		m_SquareShader.reset(Hazel::Shader::CreateShader(VertexSource, SquareFragmentSource));
		m_Camera.reset(new Hazel::PerspectiveCamera(60.0f, 16.0f / 9.0f, 0.1f, 100.0f));
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		//HZ_TRACE("DeltaTime : {0}s({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		CameraMove(ts);

		Hazel::RenderCommend::SetClearColor({ 0.1f, 0.2f, 0.8f, 1.0f });
		Hazel::RenderCommend::Clear();


		Hazel::Renderer::BeginScene(*m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), { 0.5,0.5f,0.5f });

		m_SquareShader->Bind();
		m_SquareShader->UploadUniformf3("u_Color", m_SquareColor);
		for (int y = 0; y < 1; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				glm::vec3 pos(0.5f * x, 0.5f * y, 0.0f);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_SquarePos + pos) * scale;
				Hazel::Renderer::Submit(m_SquareShader, m_SquareVAO, model);
			}
		}

		Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat3("Square Position", glm::value_ptr(m_SquarePos),
			-0.5f, 0.5f);
		ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override
	{
		Hazel::EventDispatcher dispather(e);
		dispather.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		dispather.Dispatch<Hazel::MouseMovedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnMouseMoved));
	}
private:
	std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;

	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	std::shared_ptr<Hazel::Shader> m_SquareShader;;
	std::shared_ptr<Hazel::IndexBuffer> m_SquareIBO;
	std::shared_ptr<Hazel::VertexArray> m_SquareVAO;
	glm::vec3 m_SquareColor = {0.0f,0.0f,0.0f};
	glm::vec3 m_SquarePos = { 0.0f,0.0f,0.0f };

	std::shared_ptr<Hazel::Camera> m_Camera;
private:
	void CameraMove(float deltaTime)
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
			m_Camera->KeyboardInput(Hazel::Direction::FORWARD, deltaTime);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
			m_Camera->KeyboardInput(Hazel::Direction::BACKWARD, deltaTime);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_Camera->KeyboardInput(Hazel::Direction::LEFT, deltaTime);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_Camera->KeyboardInput(Hazel::Direction::RIGHT, deltaTime);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_Camera->KeyboardInput(Hazel::Direction::ROTATE, deltaTime);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_Camera->KeyboardInput(Hazel::Direction::ROTATE_ANTI,deltaTime);
	}
	bool OnKeyPressed(Hazel::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == HZ_KEY_LEFT_ALT) 
		{
			Hazel::Application::Get().GetWindow().SwitchMouseCapture(*m_Camera);
			return true;
		}
		if (e.GetKeyCode() == HZ_KEY_R)
		{
			m_Camera->ResetCamera();
			return true;
		}
		return true;
	}
	
	bool OnMouseMoved(Hazel::MouseMovedEvent& e)
	{
		m_Camera->MouseMovement(e.GetX(), e.GetY());
		return true;
	}
};

class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		HZ_INFO("Welcome to SandBox App!");
		
		PushLayer( new ExampleLayer());
	}
	~SandBox()
	{

	}  
};


Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();

}

