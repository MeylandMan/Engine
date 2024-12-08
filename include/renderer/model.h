#pragma once
#include<renderer/mesh.h>

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"

using namespace std;

class Model
{
public:
    Model(string const& path, bool gamma = false, bool negativeY = false) : gammaCorrection(gamma), m_NegativeTexCoordY(negativeY)
    {
        loadModel(path);
    }
 
    void negateTexCoordY(string const& path, bool x) {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            for (unsigned int j = 0; j < meshes[i].vertices.size(); j++) {
                meshes[i].vertices[j].TexCoord.y = -meshes[i].vertices[j].TexCoord.y;
           }
        }
        m_NegativeTexCoordY = x;
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
    unsigned int m_DrawCall;
    bool m_NegativeTexCoordY;
};
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);