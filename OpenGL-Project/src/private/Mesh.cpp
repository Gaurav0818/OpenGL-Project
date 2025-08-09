#include "Mesh.h"

Mesh::Mesh()
    : m_vao(0), m_vbo(0), m_ibo(0), m_indexCount(0), // Initialize other members too
    m_uniformModel(-1),
    m_uniformProjection(-1),
    m_uniformDrawEdges(-1),
    m_uniformEdgeColor(-1),
    m_uniformTessLevelInner(-1),
    m_uniformTessLevelOuter(-1),
    m_uniformLightPosition(-1),
    m_uniformAmbientMaterial(-1),
    m_uniformDiffuseMaterial(-1),
    m_uniformNormalMatrix(-1) // Corrected from m_uniformModel
{
    _initMesh();
    _initShader();
    _initTransform();
}

void Mesh::draw(const glm::mat4& view, float tessInner, float tessOuter, const glm::vec3& diffuseColor)
{

    glUseProgram(m_shader->getShaderId());


    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle DEGREE, rotationAxis);
    model = glm::scale(model, scale);

    // --- Create FINAL Modelview Matrix for the shader ---
    glm::mat4 modelview = view * model; // Combine view and model

    glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, glm::value_ptr(modelview));
    // --- Fix Normal Matrix ---
    // The normal matrix should also be based on the combined modelview
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelview)));
    glUniformMatrix3fv(m_uniformNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Set tessellation levels
    glUniform1f(m_uniformTessLevelInner, tessInner);
    glUniform1f(m_uniformTessLevelOuter, tessOuter);


    glUniform3f(m_uniformAmbientMaterial, 0.04f, 0.04f, 0.04f);
    glUniform3fv(m_uniformDiffuseMaterial, 1, glm::value_ptr(diffuseColor));
    glm::vec4 lightPosition = glm::vec4(0.25f, 0.25f, 1.0f, 0.0f);
    glUniform3fv(m_uniformLightPosition, 1, glm::value_ptr(lightPosition));


    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glPatchParameteri(GL_PATCH_VERTICES, 3); // Tell OpenGL that each patch has 3 control points


    // --- First Pass: Draw filled polygons ---
    glUniform1i(m_uniformDrawEdges, 0); // Set drawEdges to false
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_PATCHES, m_indexCount, GL_UNSIGNED_INT, 0);

    // --- Second Pass: Draw black edges ---
    glUniform1i(m_uniformDrawEdges, 1); // Set drawEdges to true
    glUniform3f(m_uniformEdgeColor, 0.0f, 0.0f, 0.0f); // Set edge color to black (R, G, B)
    glLineWidth(3.0f); // Set line width for edges (adjust as needed)

    glEnable(GL_POLYGON_OFFSET_LINE); // Enable polygon offset to prevent z-fighting
    glPolygonOffset(-1.0f, -1.0f);     // Adjust these values as needed

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_PATCHES, m_indexCount, GL_UNSIGNED_INT, 0);

    // --- Reset states ---
    glDisable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to fill mode
    glLineWidth(1.0f);                       // Reset line width to default

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void Mesh::_initMesh()
{
    // Icosahedron faces (indices)
    const int Faces[] = {
        2, 1, 0,
        3, 2, 0,
        4, 3, 0,
        5, 4, 0,
        1, 5, 0,
        11, 6, 7,
        11, 7, 8,
        11, 8, 9,
        11, 9, 10,
        11, 10, 6,
        1, 2, 6,
        2, 3, 7,
        3, 4, 8,
        4, 5, 9,
        5, 1, 10,
        2, 7, 6,
        3, 8, 7,
        4, 9, 8,
        5, 10, 9,
        1, 6, 10
    };

    // Icosahedron vertices (positions)
    const float Verts[] = {
        0.000f,  0.000f,  1.000f,
        0.894f,  0.000f,  0.447f,
        0.276f,  0.851f,  0.447f,
        -0.724f,  0.526f,  0.447f,
        -0.724f, -0.526f,  0.447f,
        0.276f, -0.851f,  0.447f,
        0.724f,  0.526f, -0.447f,
        -0.276f,  0.851f, -0.447f,
        -0.894f,  0.000f, -0.447f,
        -0.276f, -0.851f, -0.447f,
        0.724f, -0.526f, -0.447f,
        0.000f,  0.000f, -1.000f
    };

    // Calculate the number of indices for the icosahedron
    m_indexCount = sizeof(Faces) / sizeof(Faces[0]);

    // Create the VAO:
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create the VBO for positions:
    glGenBuffers(1, &m_vbo); // Use m_vbo for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

    // Position attribute (location 0, assuming PositionSlot is 0)
    // The original code used PositionSlot, which implies a specific layout location.
    // Here, we use 0 to match the common practice and your existing _initMesh.
    GLsizei stride = 3 * sizeof(float); // 3 floats for position (x, y, z)
    glEnableVertexAttribArray(0); // Enable attribute location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

    // Create the VBO for indices:
    glGenBuffers(1, &m_ibo); // Use m_ibo for index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);

    // Unbind VAO and VBOs to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind IBO as well
}

void Mesh::_initShader()
{
    m_shader = std::make_unique<Shader>();

    m_shader->SetVertShaderLocation("src/shaders/vertex.vert");
    m_shader->SetTessControlShaderLocation("src/shaders/tess_control.tesc");
    m_shader->SetTessEvalShaderLocation("src/shaders/tess_eval.tese");
    m_shader->SetGeometryShaderLocation("src/shaders/geometry.geom");
    m_shader->SetFragShaderLocation("src/shaders/fragment.frag");

    m_shader->compileShader();

    m_uniformModel = glGetUniformLocation(m_shader->getShaderId(), "Modelview");
    m_uniformProjection = glGetUniformLocation(m_shader->getShaderId(), "Projection");
    m_uniformDrawEdges = glGetUniformLocation(m_shader->getShaderId(), "drawEdges");    // Get uniform location
    m_uniformEdgeColor = glGetUniformLocation(m_shader->getShaderId(), "edgeColor");  // Get uniform location
    m_uniformTessLevelInner = glGetUniformLocation(m_shader->getShaderId(), "TessLevelInner"); // Get uniform location
    m_uniformTessLevelOuter = glGetUniformLocation(m_shader->getShaderId(), "TessLevelOuter"); // Get uniform location
    m_uniformLightPosition = glGetUniformLocation(m_shader->getShaderId(), "LightPosition");
    m_uniformAmbientMaterial = glGetUniformLocation(m_shader->getShaderId(), "AmbientMaterial");
    m_uniformDiffuseMaterial = glGetUniformLocation(m_shader->getShaderId(), "DiffuseMaterial");
    m_uniformNormalMatrix = glGetUniformLocation(m_shader->getShaderId(), "NormalMatrix");



    if (g_activeWindow) // Check if g_activeWindow is valid
    {
        m_projection = glm::perspective(
            glm::radians(45.0f),
            (float)g_activeWindow->getBufferWidth() / (float)g_activeWindow->getBufferHeight(),
            0.01f,
            100.0f
        );
    }
    else
    {
        Logger::Error("g_activeWindow is null in Mesh::_initShader. Projection matrix might be incorrect.");
        // Fallback to a default projection if window is not available
        m_projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f, // Default aspect ratio
            0.01f,
            100.0f
        );
    }
}

void Mesh::_initTransform()
{
    angle = 0;
    pos = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
}
