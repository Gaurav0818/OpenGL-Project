#include "Mesh.h"

Mesh::Mesh()
{
    _initMesh();
    _initShader();
    _initTransform();
}

void Mesh::draw()
{

    glUseProgram(m_shader->getShaderId());

    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle DEGREE, rotationAxis);
    model = glm::scale(model, scale);

    glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void Mesh::_initMesh()
{
    unsigned int indices[] =
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    float vertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::_initShader()
{
    m_shader = std::make_unique<Shader>();

    m_shader->SetVertShaderLocation("src/shaders/vertex.vert");
    m_shader->SetFragShaderLocation("src/shaders/fragment.frag");

    m_shader->compileShader();

    m_uniformModel = glGetUniformLocation(m_shader->getShaderId(), "model");
    m_uniformProjection = glGetUniformLocation(m_shader->getShaderId(), "projection");

    m_projection = glm::perspective(
        45.0f,
        (float)g_activeWindow->getBufferWidth() / (float)g_activeWindow->getBufferHeight(),
        0.01f,
        100.0f
    );                 
}

void Mesh::_initTransform()
{
    angle = 0;
    pos = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
}
