#include "Shader.h"
#include <iostream>

void Shader::Bind() const { glUseProgram(m_ID); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::Destroy() { glDeleteProgram(m_ID); }

void Shader::Compile(const char* vert_source, const char* frag_source, const char* geom_source)
{
	unsigned int vertexID, fragmentID, geometryID;
	vertexID = compileSingleShader(GL_VERTEX_SHADER, vert_source);
	fragmentID = compileSingleShader(GL_FRAGMENT_SHADER, frag_source);
	if (geom_source != nullptr)
		geometryID = compileSingleShader(GL_GEOMETRY_SHADER, geom_source);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexID);
	glAttachShader(m_ID, fragmentID);
	if (geom_source != nullptr)
		glAttachShader(m_ID, geometryID);
	glLinkProgram(m_ID);
	checkStatus(m_ID, "PROGRAM");

	// Delete the shaders as they're already linked into our program and no longer necessary
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (geom_source != nullptr)
		glDeleteShader(geometryID);
}

void Shader::SetUniformFloat(std::string name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}
void Shader::SetUniformInt(std::string name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}
void Shader::SetUniformVec2(std::string name, float x, float y)
{
	glUniform2f(getUniformLocation(name), x, y);
}
void Shader::SetUniformVec2(std::string name, const glm::vec2& value)
{
	glUniform2f(getUniformLocation(name), value.x, value.y);
}
void Shader::SetUniformVec3(std::string name, float x, float y, float z)
{
	glUniform3f(getUniformLocation(name), x, y, z);
}
void Shader::SetUniformVec3(std::string name, const glm::vec3& value)
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}
void Shader::SetUniformVec4(std::string name, float x, float y, float z, float w)
{
	glUniform4f(getUniformLocation(name), x, y, z, w);
}
void Shader::SetUniformVec4(std::string name, const glm::vec4& value)
{
	glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}
void Shader::SetUniformMat(std::string name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::compileSingleShader(unsigned int gl_type, const char* source)
{
	unsigned int shaderID = glCreateShader(gl_type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);
	std::string hint = "n/a";
	switch (gl_type)
	{
		case GL_VERTEX_SHADER: hint = "VERTEX"; break;
		case GL_FRAGMENT_SHADER: hint = "FRAGMENT"; break;
		case GL_GEOMETRY_SHADER: hint = "GEOMETRY"; break;
		default: break;
	}
	checkStatus(shaderID, hint);

	return shaderID;
}

void Shader::checkStatus(unsigned int object, const std::string& hint)
{
	int success;
	char infoLog[1024];
	if (glIsProgram(object))
	{
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
			std::cout << "ERROR: Shader linking error: Type: " << hint << "\n"
					  << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR: Shader compile-time error: Type: " << hint << "\n"
					  << infoLog << std::endl;
		}
	}
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_ID, name.c_str());
	if (location == -1)
		std::cout << "WARNING: Uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
