#include "mesh.h"
#include <assimp/Importer.hpp>

Mesh::Mesh()
{

}

void Mesh::loadModel(const char *filename)
{
    Assimp::Importer importer;
   /* QFile file(path);
    if (!file.open(QI0Device::ReadOnly))
    std::cout << "Could not open file for read: " << path << std::endl;
    return;
    I
    QByteArray data = file.readAll();
    const aiScene *scene = import.ReadFileFromMemory(
    data.data(), data.size(),
    aiProcess_Triangulate I
    aiProcess_FlipUVs I
    aiProcess_GenSmoothNormals I //aiProcess_RemoveRedundantMaterials aiProcess_OptimizeMeshes I
    aiProcess_PreTransformVertices I aiProcess_ImproveCacheLocality 1 ".obj")
    if(!scene II scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE II !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    return;
    I
    processNode(scene->mRootNode, scene); needsUpdate = true;*/

}
