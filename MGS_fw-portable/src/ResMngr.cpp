#include "ResMngr.h"

#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::unordered_map<std::string, Shader>	ResourceManager::Shaders;
//std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char* vert_shader_path, const char* frag_shader_path, const char* geom_shader_path, std::string name)
{
	std::string vert_src = loadSingleShader(vert_shader_path);
	std::string frag_src = loadSingleShader(frag_shader_path);

	Shader shader;
	shader.Compile(vert_src.c_str(), frag_src.c_str());
	Shaders[name] = shader;

	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	/* Careful! This functions asumes that specified shader exists! */
	return Shaders[name];
}

/*Texture2D ResourceManager::LoadTexture(const char* file_path, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file_path, alpha);
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}*/

void ResourceManager::Clean()
{
	for (auto iter : Shaders) iter.second.Destroy();
	/*for (auto iter : Textures)
		glDeleteTextures(1, &iter.second._ID);*/
}

std::string ResourceManager::loadSingleShader(std::string file_path)
{
	std::ifstream shader_file;
	std::stringstream shader_stream;

	shader_file.open(file_path);
	shader_stream << shader_file.rdbuf();
	shader_file.close();

	return shader_stream.str();
}


//Texture2D ResourceManager::loadTextureFromFile(const char* file_path, bool alpha)
//{
//	/* Create texture object */
//	Texture2D texture;
//	if (alpha)
//	{
//		texture._Internal_Format = GL_RGBA8;
//		texture._Image_Format = GL_RGBA;
//	}
//	/* Load image and generate texture */
//	stbi_set_flip_vertically_on_load(1);
//	int width, height;
//	byte* image = stbi_load(file_path, &width, &height, 0, (texture._Image_Format == GL_RGBA) ? 4 : 3);
//	texture.Generate(width, height, image);
//	/* Free image data */
//	stbi_image_free(image);
//	return texture;
//}