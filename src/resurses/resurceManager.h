#pragma once
#include <iostream>
#include <memory>
#include <map>
namespace Render
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

class ResurceManager {
public:
	ResurceManager(const std::string& executablePath);
	~ResurceManager() = default;
	ResurceManager(const ResurceManager&) = delete;
	ResurceManager& operator=(const ResurceManager&) = delete;
	ResurceManager& operator=(ResurceManager&&) = delete;
	ResurceManager(ResurceManager&&) = delete;

	std::shared_ptr<Render::ShaderProgram>loadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Render::ShaderProgram>getShaderProgram(const std::string& shaderName);
	std::shared_ptr<Render::Texture2D>loadTexture(const std::string& textureName, const std::string& texturepath);
	std::shared_ptr<Render::Texture2D>getTexture(const std::string& textureName);
	std::shared_ptr<Render::Sprite>loadSprite(const std::string& spriteName,
											 const std::string& textureName,
											 const std::string& shaderName,
											 const unsigned int spritesWidth,
											 const unsigned int spritesHeight);
	std::shared_ptr<Render::Sprite>getSprite(const std::string& spriteName);
private:
	std::string getFilestring(const std::string& reletivFilePath) const;
	typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderProgram;

	typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> TexturesMap;
	TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Render::Sprite>> SpritesMap;
	SpritesMap m_Sprites;

	std::string m_path;

};