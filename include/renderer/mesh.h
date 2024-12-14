#pragma once
#include<renderer/Vertex.h>
#include<vector>
#include<renderer/shader.h>
#include<renderer/vao.h>
#include<renderer/vbo.h>
#include<renderer/ibo.h>
#include<renderer/textures.h>
#include<renderer/VertexBufferLayout.h>
#include<string>
#include <algorithm>

using namespace std;

class Mesh {
public:
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<MeshTexture>& textures);

    //Delete the copy constructor/assignment.
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) : VAO(other.VAO), VBO(other.VBO), EBO(other.EBO), textures(other.textures)
    {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
        textures.clear();
    }

    Mesh& operator=(Mesh&& other)
    {
        //ALWAYS check for self-assignment.
        if (this != &other)
        {
            deleteMesh();
            swap(VAO, other.VAO);
            swap(VBO, other.VBO);
            swap(EBO, other.EBO);
            swap(textures, other.textures);
        }
    }

    ~Mesh();
    void Draw(Shader& shader);
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    unsigned int VAO = 0;
private:
    unsigned int VBO = 0, EBO = 0;
    void setupMesh();
    void deleteMesh();
};