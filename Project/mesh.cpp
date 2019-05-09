#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <qfile.h>
#include <qiodevice.h>
#include <iostream>
#include <vertexformat.h>
#include "submesh.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspectorwidget.h"

Mesh::Mesh()
{

}

void Mesh::loadModel(const char *filename)
{
    Assimp::Importer import;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Could not open file for read: " << filename << std::endl;
        return;
    }

    QByteArray data = file.readAll();
    const aiScene *scene = nullptr;

    QFileInfo fileinfo;
    fileinfo.setFile(filename);
    QString extension = fileinfo.completeSuffix();
    if (!extension.compare("obj"))
    {
        scene =import.ReadFileFromMemory(
                    data.data(), data.size(),
                    aiProcess_Triangulate |
                    aiProcess_FlipUVs |
        aiProcess_GenSmoothNormals | //aiProcess_RemoveRedundantMaterials aiProcess_OptimizeMeshes I
        aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality, ".obj");
    }
    else
    {
        scene =import.ReadFileFromMemory(
                    data.data(), data.size(),
                    aiProcess_Triangulate |
                    aiProcess_FlipUVs |
        aiProcess_GenSmoothNormals | //aiProcess_RemoveRedundantMaterials aiProcess_OptimizeMeshes I
        aiProcess_PreTransformVertices | aiProcess_ImproveCacheLocality, ".fbx");
    }

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

   processNode(scene->mRootNode, scene);
   mainWindow->openGLWidget->needUpdate = true;
}


void Mesh::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    submeshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
    }
}

SubMesh* Mesh::processMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;
    // process vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }

    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0, 0, 3); vertexFormat.setVertexAttribute(1, 3 * sizeof(float), 3);

    if (mesh->HasTextureCoords(0))
        vertexFormat.setVertexAttribute(2, 6 * sizeof(float), 2);

    if (mesh->HasNormals())
    {

    }

    if (scene->HasMaterials())
    {
        aiString material_path;
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_NONE, 0, &material_path);
        qDebug("aiTextureType_NONE: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &material_path);
        qDebug("aiTextureType_DIFFUSE: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_SPECULAR, 0, &material_path);
        qDebug("aiTextureType_SPECULAR: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_AMBIENT, 0, &material_path);
        qDebug("aiTextureType_AMBIENT: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_EMISSIVE, 0, &material_path);
        qDebug("aiTextureType_EMISSIVE: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_HEIGHT, 0, &material_path);
        qDebug("aiTextureType_HEIGHT: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_NORMALS, 0, &material_path);
        qDebug("aiTextureType_NORMALS: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_SHININESS, 0, &material_path);
        qDebug("aiTextureType_SHININESS: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_OPACITY, 0, &material_path);
        qDebug("aiTextureType_OPACITY: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DISPLACEMENT, 0, &material_path);
        qDebug("aiTextureType_DISPLACEMENT: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_LIGHTMAP, 0, &material_path);
        qDebug("aiTextureType_LIGHTMAP: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_REFLECTION, 0, &material_path);
        qDebug("aiTextureType_REFLECTION: %s", material_path.C_Str());
        scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_UNKNOWN, 0, &material_path);
        qDebug("aiTextureType_UNKNOWN: %s", material_path.C_Str());
    }

    return new SubMesh(QString(mesh->mName.C_Str()), vertexFormat, &vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size());
}

void Mesh::destroy()
{
    qDebug("Destroying mesh");
    for(int i=0; i<submeshes.length(); i++)
        submeshes[i]->destroy();
    submeshes.clear();
}
