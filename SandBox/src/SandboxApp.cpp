#include <Hazel.h>
#include <imgui.h>
#include "Sandbox2D.h"

#include "hazel\Core\EntryPoint.h"
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
		: Layer("example"), //m_CameraController(1280.0f/720.0f, true),
		m_CameraController(1280.0f/720.f, 60.0f, 0.1f, 100.0f)
	{

		float vertices[] = {
//      |     --Pos--     |     -- Color --       |  -- Tex -- |   
		-0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.1f, 1.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 0.7f, 0.4f, 1.0f, 0.5f, 1.0f,

		-0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.8f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.2f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 0.2f, 0.8f, 0.1f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.8f, 0.1f, 0.2f, 1.0f, 0.0f, 1.0f
		};

		m_VertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" },
			{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
		};
		m_VertexBuffer->SetLayout(layout);

		unsigned int indices[] = { 0,1,2 };
		m_IndexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		m_VertexArray = Hazel::VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_VertexArray->UnBind();

		unsigned int SquareIndices[] = { 3,4,5,5,6,3 };
		m_SquareIBO = Hazel::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(unsigned int));

		m_SquareVAO = Hazel::VertexArray::Create();
		m_SquareVAO->AddVertexBuffer(m_VertexBuffer);
		m_SquareVAO->SetIndexBuffer(m_SquareIBO);
		m_SquareVAO->UnBind();

		std::string VertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec2 a_TexCoord;

			out vec4 v_Color;
			out vec2 v_TexCoord;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main()
			{
				gl_Position = projection * view * model * vec4(a_Position, 1.0f);
				v_Color = a_Color;
				v_TexCoord = a_TexCoord;
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
		
		m_Shader = Hazel::Shader::CreateShader("m_Shader", VertexSource, FragmentSource);
		m_SquareShader = Hazel::Shader::CreateShader("m_SquareShader", VertexSource, SquareFragmentSource);
		m_TextureShader = Hazel::ShaderLibrary::GetShader("TextureShader");

		m_Texture2D = Hazel::Texture2D::Create("./assets/Texture/siu.jpg",4);
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		// Update
		m_CameraController.Update(ts);

		// Render
		Hazel::RenderCommend::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Hazel::RenderCommend::Clear();


		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), { 0.5,0.5f,0.5f });

		m_SquareShader->Bind();
		m_SquareShader->UploadUniformf3("u_Color", m_SquareColor);
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				glm::vec3 pos(0.55f * x, 0.55f * y, 0.0f);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_SquarePos + pos) * scale;
				Hazel::Renderer::Submit(m_SquareShader, m_SquareVAO, model);
			}
		}
		m_Texture2D->Bind(0);
		m_TextureShader->Bind();
		m_TextureShader->UploadUniformi1("u_Texture", 0);
		Hazel::Renderer::Submit(m_TextureShader, m_SquareVAO);

		// Triangle
		//Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat3("Square Position", glm::value_ptr(m_SquarePos),
			-1.5f, 1.5f);
		ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	//Hazel::OrthographicCameraController m_CameraController;
	Hazel::PerspectiveCameraController m_CameraController;

	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;

	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_SquareShader;
	Hazel::Ref<Hazel::IndexBuffer> m_SquareIBO;
	Hazel::Ref<Hazel::VertexArray> m_SquareVAO;
	glm::vec3 m_SquareColor = {0.0f,0.0f,0.0f};
	glm::vec3 m_SquarePos = { 0.0f,0.0f,-0.5f };

	Hazel::Ref<Hazel::Shader> m_TextureShader;
	Hazel::Ref<Hazel::Texture2D> m_Texture2D;  

};

class SandBox : public Hazel::Application
{
public:
	SandBox()
	{
		HZ_INFO("Welcome to SandBox App!");
		
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~SandBox()
	{

	}  
};


Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();

}

