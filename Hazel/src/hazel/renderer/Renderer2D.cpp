#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommend.h"

namespace Hazel {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};
	
	static Renderer2DStorage* s_Renderer2DStorage;


	void  Renderer2D::Init()
	{
		s_Renderer2DStorage = new Renderer2DStorage();
		

		float vertices[] = {
			//      |     --Pos--     |   --TexCoord-- |
					-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
					 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
					 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
					-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
		};
		squareVB->SetLayout(layout);

		Ref<IndexBuffer> squareIB;
		unsigned int indices[] = { 0,1,2,2,3,0 };
		squareIB = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		s_Renderer2DStorage->QuadVertexArray = VertexArray::Create();
		s_Renderer2DStorage->QuadVertexArray->AddVertexBuffer(squareVB);
		s_Renderer2DStorage->QuadVertexArray->SetIndexBuffer(squareIB);
		s_Renderer2DStorage->QuadVertexArray->UnBind();

		// In Application.cpp - Hazel::ShaderLibrary::Init();
		// HZ_ASSERT(Hazel::ShaderLibrary::IsInit(), "ShaderLibrary not initialized!");

		s_Renderer2DStorage->TextureShader = Hazel::Shader::CreateShader("./assets/Shader/TextureShader.glsl");

		s_Renderer2DStorage->WhiteTexture = Hazel::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DStorage->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Renderer2DStorage;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Renderer2DStorage->TextureShader->Bind();
		s_Renderer2DStorage->TextureShader->UploadUniformMat4("view", camera.GetViewMatrix());
		s_Renderer2DStorage->TextureShader->UploadUniformMat4("projection", camera.GetProjectionMatrix());

	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Renderer2DStorage->TextureShader->UploadUniformf4("u_Color", color);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size, 0.0f});
		s_Renderer2DStorage->TextureShader->UploadUniformMat4("model", model);

		s_Renderer2DStorage->WhiteTexture->Bind(0);
		s_Renderer2DStorage->TextureShader->UploadUniformi1("u_Texture", 0);

		s_Renderer2DStorage->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Renderer2DStorage->QuadVertexArray);
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, uint32_t slot)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, slot);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,uint32_t slot)
	{

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size, 0.0f });
		s_Renderer2DStorage->TextureShader->UploadUniformMat4("model", model);
		s_Renderer2DStorage->TextureShader->UploadUniformf4("u_Color", glm::vec4(1.0f));
		texture->Bind(slot); //slot = 0;
		s_Renderer2DStorage->TextureShader->UploadUniformi1("u_Texture", slot);

		s_Renderer2DStorage->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Renderer2DStorage->QuadVertexArray);

		texture->UnBind();
	}
}