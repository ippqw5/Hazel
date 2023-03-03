#include "hzpch.h"
#include "OpenGLShader.h"

namespace Hazel {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		HZ_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}



	std::string OpenGLShader::Readfile(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string sourcecode;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			sourcecode.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&sourcecode[0], sourcecode.size());
			in.close();
		}
		else
		{
			HZ_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return sourcecode;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{

		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shader_src;
		//Searches the string for the character that matches any of the characters specified in its arguments.
		// find(),find_first_of(),find_last_of()...
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t typeToken_pos = source.find(typeToken, 0);

		while (typeToken_pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", typeToken_pos);
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			size_t begin = typeToken_pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type)
				, "Invaild shader type!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			typeToken_pos = source.find(typeToken, nextLinePos);

			shader_src[ShaderTypeFromString(type)] = source.substr(
				nextLinePos,
				typeToken_pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
			);
		}
		return shader_src;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		HZ_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		HZ_CORE_ASSERT(shaderSources.size() <= 2, "We only support two shaders for now");
		std::array<GLenum, 2> glShaderIDs = {0};
		int glShaderIDsIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum key = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(key);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				HZ_CORE_ERROR("{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			}
			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDsIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto shader : glShaderIDs)
				glDeleteShader(shader);
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure!");
		}
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string sourcecode = Readfile(filepath);
		auto shaderSources = Preprocess(sourcecode);
		Compile(shaderSources);

		/// Extract name from filepath 
		// eg:
		//  ./assets/Texture/TextureShader.glsl
		//  ./assets/Texture/TextureShader
		//  TextureShader.glsl
		auto lastSlash = filepath.find_last_of("/\\");
		auto firstChar = (lastSlash == std::string::npos ? 0 : lastSlash + 1);

		auto lastDot = filepath.rfind('.');

		auto count = (lastDot == std::string::npos ? filepath.size() - firstChar : lastDot - firstChar);
		m_Name = filepath.substr(firstChar, count);
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_Name(name)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		HZ_PROFILE_FUNCTION();
		glUseProgram(0);
	}


	void OpenGLShader::UploadUniformi1(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformf1(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformf3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void OpenGLShader::UploadUniformf4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.r, value.g, value.b, value.a);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}