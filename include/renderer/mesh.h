#pragma once
#include<renderer/Vertex.h>
#include<vector>
#include<renderer/shader.h>
#include<renderer/vao.h>
#include<renderer/vbo.h>
#include<renderer/ibo.h>
#include<renderer/textures.h>

class Mesh{
public:
	Mesh(std::vector<ShortTVertex> vertices, std::vector<ibo> indices, 
		std::vector<Texture> textures);
	void Draw(Shader& shader);
	private:
		std::vector<ShortTVertex> m_MeshVertices;
		std::vector<ibo> m_MeshIndices;
		std::vector<Texture> m_MeshTextures;
		vao m_MeshVAO;
		vbo m_MeshVBO;
		ibo m_MeshIBO;
		void setupMesh();
};
