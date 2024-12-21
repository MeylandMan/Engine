#include<renderer/mesh.h>

Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<MeshTexture>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
}

Mesh::~Mesh() {
    //deleteMesh();
}

void Mesh::setupMesh() {
    m_Vbo = vbo(&vertices[0], vertices.size() * sizeof(Vertex));
    m_Ibo = ibo(&indices[0], indices.size() * sizeof(unsigned int));

    m_Layout.Push<float>(3);
    m_Layout.Push<float>(2);
    m_Layout.Push<float>(3);
    m_Layout.Push<float>(3);
    m_Layout.Push<float>(3);
    m_Layout.Push<unsigned int>(4);
    m_Layout.Push<float>(4);
    m_Vao.AddBuffer(m_Vbo, m_Layout);

}

void Mesh::deleteMesh() {
    for (MeshTexture texture : textures) {
        glDeleteTextures(1, &texture.id);
        texture.id = 0;
    }
}

void Mesh::Draw(Shader & shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        shader.setUniform1i((name + number).c_str(), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    m_Vao.Bind();
    m_Ibo.Bind();
    glDrawElements(GL_TRIANGLES, m_Ibo.GetCount(), GL_UNSIGNED_INT, 0);

    m_Vao.Unbind();
    m_Ibo.Unbind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}