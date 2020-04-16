#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	/* Empty constructor */
	Shader() : m_ID(0) {}
	/* Sets the current shader as active */
	void Bind() const;
	void Unbind() const;
	/* Adequately deletes shader program */
	void Destroy();
	/* Compile program shader from given source */
	void Compile(const char* vert_source, const char* frag_source, const char* geom_source = nullptr);
	/* Utility functions */
    void SetUniformFloat(std::string name, float value);
    void SetUniformInt	(std::string name, int value);
    void SetUniformVec2	(std::string name, float x, float y);
    void SetUniformVec2	(std::string name, const glm::vec2 &value);
    void SetUniformVec3	(std::string name, float x, float y, float z);
    void SetUniformVec3	(std::string name, const glm::vec3 &value);
    void SetUniformVec4	(std::string name, float x, float y, float z, float w);
    void SetUniformVec4	(std::string name, const glm::vec4 &value);
	void SetUniformMat	(std::string name, const glm::mat4& matrix);
private:
	unsigned int m_ID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
private:
	unsigned int compileSingleShader(unsigned int gl_type, const char* source);
	void checkStatus(unsigned int object, const std::string& hint);
	int getUniformLocation(const std::string& name);
};

#endif