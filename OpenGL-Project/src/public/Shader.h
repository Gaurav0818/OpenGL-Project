#pragma once

#include "Config.h"

class Shader
{
public:
	Shader() = default;
	~Shader() = default;
	
	Shader(std::string vertShaderLocation, std::string fragShaderLocation) :
		m_vertShaderLoc(std::move(vertShaderLocation)), m_fragShaderLoc(std::move(fragShaderLocation)) 
	{
		m_shaderID = 0;
	}


	void compileShader();

	unsigned int getShaderId() const {	return m_shaderID; }

	void SetVertShaderLocation(std::string vertShaderLocation);
	void SetFragShaderLocation(std::string fragShaderLocation);

private:
	unsigned int m_shaderID;
	std::string m_vertShaderLoc, m_fragShaderLoc;

	void _getShaderCode(std::string& shaderCode, std::string& location);
	void _addShader(unsigned int theProgram, GLenum shaderType, std::string& location);
};
