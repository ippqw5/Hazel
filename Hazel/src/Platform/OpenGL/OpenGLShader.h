#pragma once
#include "hazel\renderer\Shader.h"
#include <string>
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Hazel {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		inline virtual std::string GetName() const override { return m_Name; }
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void UploadUniformi1(const std::string& name, int value) override;
		virtual void UploadUniformf3(const std::string& name, const glm::vec3& value) override;
		virtual void UploadUniformf4(const std::string& name, const glm::vec4& value) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	private:
		std::string Readfile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	};
}