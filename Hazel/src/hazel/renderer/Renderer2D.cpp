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
	
	static Renderer2DStorage* s_Data;


	void  Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();
		s_Data = new Renderer2DStorage();
		

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

		s_Data->QuadVertexArray = VertexArray::Create();
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
		s_Data->QuadVertexArray->UnBind();

		// In Application.cpp - Hazel::ShaderLibrary::Init();
		// HZ_ASSERT(Hazel::ShaderLibrary::IsInit(), "ShaderLibrary not initialized!");

		s_Data->TextureShader = Hazel::Shader::CreateShader("./assets/Shader/TextureShader.glsl");

		s_Data->WhiteTexture = Hazel::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		HZ_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->UploadUniformMat4("view", camera.GetViewMatrix());
		s_Data->TextureShader->UploadUniformMat4("projection", camera.GetProjectionMatrix());

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
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->UploadUniformf4("u_Color", color);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size, 0.0f});
		s_Data->TextureShader->UploadUniformMat4("model", model);
		s_Data->TextureShader->UploadUniformf1("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind(0);
		s_Data->TextureShader->UploadUniformi1("u_Texture", 0);

		s_Data->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Data->QuadVertexArray);
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float TilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, TilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float TilingFactor)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size, 0.0f });
		s_Data->TextureShader->UploadUniformMat4("model", model);
		s_Data->TextureShader->UploadUniformf4("u_Color", glm::vec4(1.0f));
		s_Data->TextureShader->UploadUniformf1("u_TilingFactor", TilingFactor);
		texture->Bind(0); //slot = 0;
		s_Data->TextureShader->UploadUniformi1("u_Texture", 0);

		s_Data->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Data->QuadVertexArray);

		texture->UnBind();
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), { size, 0.0f });
		s_Data->TextureShader->UploadUniformf4("u_Color", color);
		s_Data->TextureShader->UploadUniformMat4("model", model);
		s_Data->TextureShader->UploadUniformf1("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind(0);
		s_Data->TextureShader->UploadUniformi1("u_Texture", 0);

		s_Data->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float TilingFactor, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, TilingFactor, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float TilingFactor, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size, 0.0f });
		s_Data->TextureShader->UploadUniformMat4("model", model);
		s_Data->TextureShader->UploadUniformf4("u_Color", color);
		s_Data->TextureShader->UploadUniformf1("u_TilingFactor", TilingFactor);
		texture->Bind(0); //slot = 0;
		s_Data->TextureShader->UploadUniformi1("u_Texture", 0);

		s_Data->QuadVertexArray->Bind();
		RenderCommend::DrawIndexed(s_Data->QuadVertexArray);

		texture->UnBind();
	}
}