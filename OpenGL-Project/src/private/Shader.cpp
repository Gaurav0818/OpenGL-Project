#include "Shader.h"

void Shader::compileShader()
{
    m_shaderID = glCreateProgram();

    if (!m_shaderID)
    {
        Logger::Error("Error Creating shader program!");
        return;
    }

    _addShader(m_shaderID, GL_VERTEX_SHADER, m_vertShaderLoc);
    _addShader(m_shaderID, GL_TESS_CONTROL_SHADER, m_tessControlShaderLoc);
    _addShader(m_shaderID, GL_TESS_EVALUATION_SHADER, m_tessEvalShaderLoc);
    _addShader(m_shaderID, GL_GEOMETRY_SHADER, m_geometryShaderLoc);
    _addShader(m_shaderID, GL_FRAGMENT_SHADER, m_fragShaderLoc);

    int result = 0;

    glLinkProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        char eLog[1024] = { 0 };
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        Logger::Error(std::string("Error linking program: ") + eLog);
        glDeleteProgram(m_shaderID); // Clean up on failure
        m_shaderID = 0;
        return;
    }

    glValidateProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        char eLog[1024] = { 0 };
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        Logger::Error(std::string("Error Validating program: ") + eLog);
        glDeleteProgram(m_shaderID); // Clean up on failure
        m_shaderID = 0;
        return;
    }
}

void Shader::SetVertShaderLocation(std::string vertShaderLocation)
{
    m_vertShaderLoc = std::move(vertShaderLocation);
}

void Shader::SetFragShaderLocation(std::string fragShaderLocation)
{
    m_fragShaderLoc = std::move(fragShaderLocation);
}

void Shader::SetTessEvalShaderLocation(std::string tessEvalLoc)
{
    m_tessEvalShaderLoc = std::move(tessEvalLoc);
}

void Shader::SetTessControlShaderLocation(std::string tessControlLoc)
{
    m_tessControlShaderLoc = std::move(tessControlLoc);
}

void Shader::SetGeometryShaderLocation(std::string geometryLoc) {
    m_geometryShaderLoc = std::move(geometryLoc);
}

void Shader::_getShaderCode(std::string& shaderCode, std::string& location)
{
    std::ifstream file;
    std::string line;
    std::stringstream ss;

    file.open(location);
    if (!file.is_open())
    {
        Logger::Error(std::string("failed to open file ") + location);
        shaderCode = ""; // Ensure shaderCode is empty if file not found
        return;
    }
    while (std::getline(file, line))
    {
        ss << line << "\n";
    }
    file.close();
    shaderCode = ss.str();
}

void Shader::_addShader(unsigned int theProgram, GLenum shaderType, std::string& location)
{
    std::string shaderCode;
    unsigned int theShader = glCreateShader(shaderType);
    _getShaderCode(shaderCode, location);
    const char* theCode[1];
    theCode[0] = shaderCode.c_str();

    int codeLength[1];
    codeLength[0] = shaderCode.length();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    int result = 0;

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        char eLog[1000] = { 0 };
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        Logger::Error(std::string("Error Compiling ") + std::to_string(shaderType) + " Shader :" + eLog);
        glDeleteShader(theShader);
        return;
    }

    glAttachShader(theProgram, theShader);
}
