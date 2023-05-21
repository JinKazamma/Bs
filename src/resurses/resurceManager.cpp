#include "resurceManager.h"
#include "../render/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>

ReurceManager::ReurceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}
std::string ReurceManager::getFilestring(const std::string& reletivFilePath)const
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
std::shared_ptr<Render::ShaderProgram> ReurceManager::loadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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
std::shared_ptr<Render::ShaderProgram>ReurceManager::getShaderProgram(const std::string& shaderName) 
{
	ShaderProgramsMap::const_iterator it = m_shaderProgram.find(shaderName);
	if (it != m_shaderProgram.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program: " << shaderName << std::endl;
	return nullptr;
}