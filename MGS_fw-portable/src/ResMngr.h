#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>

#include "Shader.h"
//#include "texture2D.hpp"

class ResourceManager
{
public:
	static std::unordered_map<std::string, Shader>	Shaders;
	//static std::map<std::string, Texture2D> Textures;
public:
	static Shader LoadShader(const char* vert_shader_path, const char* frag_shader_path, const char* geom_shader_path, std::string name);
	static Shader GetShader(std::string name);
	//static Texture2D LoadTexture(const char* file_path, bool alpha, std::string name);
	//static Texture2D GetTexture(std::string name);
	static void Clean();
private:
	ResourceManager() {}
	static std::string loadSingleShader(std::string file_path);
	//static Texture2D loadTextureFromFile(const char* file_path, bool alpha);
};

#endif