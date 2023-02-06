#include "hzpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform\OpenGL\OpenGLShader.h"

namespace Hazel {

	Ref<Shader> Shader::CreateShader(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::CreateShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="shader"></param>
	/// 
	ShaderLibrary* ShaderLibrary::s_Instance = nullptr;

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HZ_CORE_ASSERT(!IsExist(name), "Shader already exist");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::CreateShader(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::CreateShader(filepath);
		Add(name, shader);
		return shader;
	}


	static std::vector<std::string> shaders =
	{
		"TextureShader.glsl"
	};


	void ShaderLibrary::Init()
	{
		s_Instance = new ShaderLibrary;
		auto root = "./assets/Shader/";
		for (auto& f : shaders)
		{
			s_Instance->Load(root + f);
		}

	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		return s_Instance->Get(name);
	}	
}