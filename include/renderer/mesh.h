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

using namespace std;

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures);
    void Draw(Shader& shader);
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<MeshTexture> textures;
    unsigned int VAO;
private:
    unsigned int VBO, EBO;
    void setupMesh();
};