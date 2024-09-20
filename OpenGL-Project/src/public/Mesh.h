#pragma once

#include "Config.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	~Mesh() = default;
	
	void draw();

	glm::vec3 pos;
	glm::vec3 scale;
	float angle;

private:
	unsigned int m_vao, m_vbo, m_uniformModel;

	std::unique_ptr<Shader> m_shader;

	void _initMesh();
	void _initShader();
	void _initTransform();
};