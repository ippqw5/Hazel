#pragma once
#include "hazel\renderer\Shader.h"
#include <string>
#include <glm\glm.hpp>
namespace Hazel {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void UploadUniformf3(const std::string& name, const glm::vec3& value) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t m_RendererID;
	};
}