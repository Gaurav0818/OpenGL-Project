#pragma once

#include "Config.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	~Mesh() = default;
	
	void draw(const glm::mat4& view, float tessInner, float tessOuter, const glm::vec3& diffuseColor);

private:
	void _initMesh();
	void _initShader();
	void _initTransform();

public:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float angle;


	void GLCheckError()
	{
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << err << std::endl;
		}
	}

private:
	unsigned int m_vao, m_ibo, m_vbo, m_indexCount;
	unsigned int m_uniformModel, m_uniformProjection, m_uniformAmbientMaterial, 
		m_uniformDiffuseMaterial, m_uniformLightPosition;
	GLuint m_uniformTessLevelInner;
	GLuint m_uniformTessLevelOuter;
	GLuint m_uniformDrawEdges;  // New uniform location
	GLuint m_uniformEdgeColor; // New uniform location
	GLuint m_uniformNormalMatrix;


	glm::mat4 m_projection;

	std::unique_ptr<Shader> m_shader;
};
