#pragma once
#include<renderer/renderer.h>


using namespace std;

class Mesh {
public:
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<MeshTexture>& textures);
    ~Mesh();

	/*
	*/
	
	//Delete the copy constructor/assignment.
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other) { }
	
	Mesh& operator=(Mesh&& other)
	{
		//ALWAYS check for self-assignment.
		if (this != &other)
		{
			std::swap(vertices, other.vertices);
			std::swap(indices, other.indices);
			std::swap(textures, other.textures);
			deleteMesh();
		}
	}

    void Draw(Shader& shader);
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    unsigned int VAO;
    vao m_Vao;
private:
	vbo m_Vbo = vbo(&vertices[0], sizeof(float));
	ibo m_Ibo = ibo(&indices[0], sizeof(unsigned int));
	VertexBufferLayout m_Layout;
    unsigned int VBO, EBO;
    void setupMesh();
    void deleteMesh();
};