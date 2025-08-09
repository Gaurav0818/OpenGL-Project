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
	void SetTessEvalShaderLocation(std::string tessEvalLoc);
	void SetTessControlShaderLocation(std::string tessControlLoc);
	void SetGeometryShaderLocation(std::string geometryLoc);

private:
	unsigned int m_shaderID;
	std::string m_vertShaderLoc, m_fragShaderLoc, m_tessControlShaderLoc, m_tessEvalShaderLoc, m_geometryShaderLoc;

	void _getShaderCode(std::string& shaderCode, std::string& location);
	void _addShader(unsigned int theProgram, GLenum shaderType, std::string& location);
};
