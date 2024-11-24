#include<renderer/mesh.h>

Mesh::Mesh(std::vector<ShortTVertex> vertices, std::vector<unsigned int> indices, 
	std::vector<Texture> textures) :
	m_MeshVertices(vertices), m_MeshIndices(indices), m_MeshTextures(textures),
	m_MeshVBO(vbo(nullptr, 0)), m_MeshIBO(ibo(nullptr, 0)){
	setupMesh();
}

void Mesh::Draw(Shader& shader) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	shader.bind();
	for (unsigned int i = 0; i < m_MeshTextures.size(); i++)
	{
		m_MeshTextures[i].Bind(i);
		std::string number;
		std::string name = m_MeshTextures[i].getType();
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader.setUniform1i(("material." + name + number).c_str(), i);
		m_MeshTextures[i].Unbind();
	}

	// draw mesh
	m_MeshVAO.Bind();
	m_MeshIBO.Bind();

	glDrawElements(GL_TRIANGLES, m_MeshIBO.GetCount(), GL_UNSIGNED_INT, nullptr);
	m_MeshVAO.Unbind();
}
void Mesh::setupMesh() {

	m_MeshVAO = vao();
	m_MeshVBO = vbo(&m_MeshVertices);
	m_Layout.PushShort<float>(3, 1);
	m_Layout.PushShort<float>(2, 1);
	m_Layout.PushShort<float>(3, 1);
	m_MeshVAO.AddBuffer(m_MeshVBO, m_Layout);
	m_MeshIBO = ibo(&m_MeshIndices);
}