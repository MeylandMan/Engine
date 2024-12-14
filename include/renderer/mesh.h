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