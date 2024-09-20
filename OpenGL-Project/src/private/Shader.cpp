#include "Shader.h"

void Shader::compileShader()
{
    m_shaderID = glCreateProgram();

    if (!m_shaderID)
    {
        std::cerr << "Error Creating shader program!" << std::endl;
        return;
    }

    _addShader(m_shaderID, GL_VERTEX_SHADER, m_vertShaderLoc);
    _addShader(m_shaderID, GL_FRAGMENT_SHADER, m_fragShaderLoc);

    int result = 0;

    glLinkProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        char eLog[1024] = { 0 };
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error linking program: " << eLog;
        return;
    }

    glValidateProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        char eLog[1024] = { 0 };
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error Validating program: " << eLog;
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

void Shader::_getShaderCode(std::string& shaderCode, std::string& location)
{
    std::ifstream file;
    std::string line;
    std::stringstream ss;

    file.open(location);
    if (!file.is_open())
    {
        std::cout << "failed to open file " << location << std::endl;
    }
    while (std::getline(file, line))
    {
        ss << line << "\n";
    }

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
    codeLength[0] = strlen(shaderCode.c_str());

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    int result = 0;

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        char eLog[1000] = { 0 };
        glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
        std::cout << "Error Compiling " << shaderType << " Shader :" << eLog;
        return;
    }

    glAttachShader(theProgram, theShader);
}
