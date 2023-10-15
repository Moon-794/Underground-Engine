#ifndef MODEL
#define MODEL

#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
    public:
        Model(char *path)
        {
            LoadModel(path);
        }
        void Draw(Shader &shader);
    private:
        std::vector<Mesh> meshes;
        std::string directory;

        void LoadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif