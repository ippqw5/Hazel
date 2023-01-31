#pragma once
#include <string>
#include <glm\glm.hpp>
namespace Hazel {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniformf3(const std::string& name, const glm::vec3& value) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
	};
}