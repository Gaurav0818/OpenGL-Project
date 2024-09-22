#pragma once

#include "Config.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	~Mesh() = default;
	
	void draw();

private:
	void _initMesh();
	void _initShader();
	void _initTransform();

public:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float angle;

private:
	unsigned int m_vao, m_ibo, m_vbo;
	unsigned int m_uniformModel, m_uniformProjection;

	glm::mat4 m_projection;

	std::unique_ptr<Shader> m_shader;
};
