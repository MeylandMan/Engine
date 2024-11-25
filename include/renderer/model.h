#pragma once
#include<renderer/mesh.h>

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"

using namespace std;

class Model
{
public:
    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);

    vector<MeshTexture> textures_loaded;
    vector<Mesh>meshes;
    string directory;
    bool gammaCorrection;

private:
    void loadModel(string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);