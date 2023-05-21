#pragma once
#include <iostream>
#include <memory>
#include <map>
namespace Render
{
	class ShaderProgram;
}

class ReurceManager {
public:
	ReurceManager(const std::string& executablePath);
	~ReurceManager() = default;
	ReurceManager(const ReurceManager&) = delete;
	ReurceManager& operator=(const ReurceManager&) = delete;
	ReurceManager& operator=(ReurceManager&&) = delete;
	ReurceManager(ReurceManager&&) = delete;

	std::shared_ptr<Render::ShaderProgram>loadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Render::ShaderProgram>getShaderProgram(const std::string& shaderName);
	
private:
	std::string getFilestring(const std::string& reletivFilePath) const;
	typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderProgram;

	std::string m_path;



};