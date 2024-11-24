#include<renderer/mesh.h>

Mesh::Mesh(std::vector<ShortTVertex> vertices, std::vector<ibo> indices, std::vector<Texture> textures) {
	m_MeshVertices = vertices;
	m_MeshIndices = indices;
	m_MeshTextures = textures;
	setupMesh();
}

void Mesh::Draw(Shader& shader) {

}
void Mesh::setupMesh() {
	m_MeshVAO = vao();
	m_MeshVBO = vbo(m_MeshVertices, sizeof(m_MeshVertices));
	m_Layout.PushShort<float>(3, 1);
	m_Layout.PushShort<float>(2, 1);
	m_Layout.PushShort<float>(3, 1);
	m_MeshVAO.AddBuffer(m_Vbo, m_Layout);
	m_MeshIBO = ibo(m_MeshIndices, sizeof(m_MeshIndices));
}