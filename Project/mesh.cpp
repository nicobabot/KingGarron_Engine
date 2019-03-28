#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <qfile.h>
#include <qiodevice.h>
#include <iostream>


Mesh::Mesh()
{

}

void Mesh::loadModel(const char *filename)
{
    Assimp::Importer import;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
    std::cout << "Could not open file for read: " << filename << std::endl;
    return;
    }



    QByteArray data = file.readAll();
    const aiScene *scene = import.ReadFileFromMemory(
                data.data(), data.size(),
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
    aiProcess_GenSmoothNormals | //aiProcess_RemoveRedundantMaterials aiProcess_OptimizeMeshes I
    aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality, ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    return;
    }
   //processNode(scene->mRootNode, scene);
   //needsUpdate = true;

}
