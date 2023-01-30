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
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.8f, 0.5f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.5f, 0.7f, 0.4f, 1.0f
		};

		m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);

		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray.reset(Hazel::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string VertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			uniform mat4 view;
			uniform mat4 projection;
			void main()
			{
				gl_Position = projection * view * vec4(a_Position, 1.0f);
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

		m_Shader.reset(new Hazel::Shader(VertexSource, FragmentSource));
		m_Camera.reset(new Hazel::PerspectiveCamera(60.0f, 16.0f / 9.0f, 0.1f, 100.0f));
	}

	void OnUpdate() override
	{
		Hazel::RenderCommend::SetClearColor({ 0.1f, 0.2f, 0.8f, 1.0f });
		Hazel::RenderCommend::Clear();


		Hazel::Renderer::BeginScene(*m_Camera);
		Hazel::Renderer::Submit(m_Shader, m_VertexArray);
		Hazel::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("test");
		//ImGui::Text("heeee");
		//ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override
	{
		Hazel::EventDispatcher dispather(e);
		dispather.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		dispather.Dispatch<Hazel::MouseMovedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnMouseMoved));
	}
private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::Camera> m_Camera;
private:
	bool OnKeyPressed(Hazel::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == HZ_KEY_LEFT_ALT)
			Hazel::Application::Get().GetWindow().SwitchMouseCapture(*m_Camera);
		else if (e.GetKeyCode() == HZ_KEY_W)
			m_Camera->KeyboardInput(Hazel::Direction::FORWARD);
		else if (e.GetKeyCode() == HZ_KEY_S)
			m_Camera->KeyboardInput(Hazel::Direction::BACKWARD);
		else if (e.GetKeyCode() == HZ_KEY_A)
			m_Camera->KeyboardInput(Hazel::Direction::LEFT);
		else if (e.GetKeyCode() == HZ_KEY_D)
			m_Camera->KeyboardInput(Hazel::Direction::RIGHT);
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

