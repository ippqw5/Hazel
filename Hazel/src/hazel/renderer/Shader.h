#pragma once
#include "hazel\Core\Core.h"
#include <string>
#include <glm\glm.hpp>
namespace Hazel {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual std::string GetName() const = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniformi1(const std::string& name, int value) = 0;
		virtual void UploadUniformf3(const std::string& name, const glm::vec3& value) = 0;
		virtual void UploadUniformf4(const std::string& name, const glm::vec4& value) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Ref<Shader> CreateShader(const std::string& filepath);
		static Ref<Shader> CreateShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};


	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		inline Ref<Shader> Get(const std::string& name)
		{
			HZ_CORE_ASSERT(IsExist(name), "Shader no exist");
			return m_Shaders[name];
		}

		inline bool IsExist(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); }
	public:
		static void Init();
		static Ref<Shader> GetShader(const std::string& name);
		static bool IsInit() { return m_IsInit; }
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		static ShaderLibrary* s_Instance;
		static bool m_IsInit;
	};
}