#include "resurceManager.h"
#include "../render/ShaderProgram.h"
#include "../render/Texture2D.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "../render/sprite.h"

ResurceManager::ResurceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}
std::string ResurceManager::getFilestring(const std::string& reletivFilePath)const
{
	std::ifstream f;
	f.open(m_path + "/" + reletivFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to oppen file: " << reletivFilePath << std::endl;
		return std::string{};
	}
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
std::shared_ptr<Render::ShaderProgram> ResurceManager::loadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFilestring(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "NO vertex shader!" << std::endl;
		return nullptr;
	}
	std::string fragmentString = getFilestring(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "NO fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Render::ShaderProgram >& newShader = m_shaderProgram.emplace(shaderName, std::make_shared<Render::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Cant load shader program: \n"
		<< "Vertex " << vertexPath << "\n"
		<< "Fragment" << fragmentPath << std::endl;
	return nullptr;
}
std::shared_ptr<Render::ShaderProgram>ResurceManager::getShaderProgram(const std::string& shaderName) 
{
	ShaderProgramsMap::const_iterator it = m_shaderProgram.find(shaderName);
	if (it != m_shaderProgram.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program: " << shaderName << std::endl;
	return nullptr;
}
std::shared_ptr<Render::Texture2D>ResurceManager::loadTexture(const std::string& textureName, const std::string& texturepath)
{
	int channels = 0;
	int widht = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturepath).c_str(), &widht, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "cant load image " << textureName << std::endl;
		return nullptr;
	}
	std::shared_ptr<Render::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<Render::Texture2D>(widht,
																														height,
																														pixels,
																														channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}
std::shared_ptr<Render::Texture2D>ResurceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the textures program: " << textureName << std::endl;
	return nullptr;
}
std::shared_ptr<Render::Sprite>ResurceManager::loadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spritesWidth,
	const unsigned int spritesHeight)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Cant find the textures program: " << textureName <<" for sprite: "<<spriteName<< std::endl;
	}
	auto pShader= getShaderProgram(shaderName);
	if (!pShader)
	{
		std::cerr << "Cant find the shader: " << shaderName << "for sprite: " << shaderName << std::endl;
	}
	std::shared_ptr<Render::Sprite> newSprite = m_Sprites.emplace(spriteName,
																  std::make_shared<Render::Sprite>(pTexture,
																  pShader,
																  glm::vec2(0.f, 0.f),
		                                                          glm::vec2(spritesWidth, spritesHeight))).first->second;
	return newSprite;
}
std::shared_ptr<Render::Sprite>ResurceManager::getSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = m_Sprites.find(spriteName);
	if (it != m_Sprites.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the sprite program: " << spriteName << std::endl;
	return nullptr;
}
