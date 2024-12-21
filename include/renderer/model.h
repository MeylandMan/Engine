#pragma once
#include<renderer/mesh.h>

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"

#include <imgui.h>
#include <backends/imfilebrowser.h>

using namespace std;

class Model
{
public:
    Model(string& path, bool gamma = false, bool negativeY = false) : gammaCorrection(gamma), m_NegativeTexCoordY(negativeY)
    {
        loadModel(path);
    }
    

    void Draw(Shader& shader);

    vector<MeshTexture> textures_loaded;
    vector<Mesh>meshes;
    string directory;
    bool gammaCorrection;
    

private:
    void loadModel(string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    unsigned int m_DrawCall;
    bool m_NegativeTexCoordY;
};

void removeBackHash(string& str);
void removeBackHash(const char* str);

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);