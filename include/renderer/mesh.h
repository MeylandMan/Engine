#pragma once
#include<renderer/Vertex.h>
#include<vector>
#include<renderer/shader.h>
#include<renderer/vao.h>
#include<renderer/vbo.h>
#include<renderer/ibo.h>
#include<renderer/textures.h>
#include<renderer/VertexBufferLayout.h>
#include<renderer/renderer.h>

class Mesh{
public:
	Mesh(std::vector<ShortTVertex> vertices, std::vector<unsigned int> indices, 
		std::vector<Texture> textures);
	void Draw(Shader& shader);
	std::vector<ShortTVertex> getVertices() { return m_MeshVertices; }
	std::vector<unsigned int> getIndices() { return m_MeshIndices; }
	std::vector<Texture> getTextures() { return m_MeshTextures; }

	vao getVao() const { return m_MeshVAO; }
	vbo getVbo() const { return m_MeshVBO; }
	ibo getIbo() const { return m_MeshIBO; }
	private:
		std::vector<ShortTVertex> m_MeshVertices;
		std::vector<unsigned int> m_MeshIndices;
		std::vector<Texture> m_MeshTextures;
		vao m_MeshVAO;
		vbo m_MeshVBO;
		ibo m_MeshIBO;
		VertexBufferLayout m_Layout;
		void setupMesh();
};
