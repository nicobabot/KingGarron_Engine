#ifndef MESH_H
#define MESH_H
#include<QVector>
#include <assimp/scene.h>

class VertexFormat;
class SubMesh;

class Mesh
{
public:
    Mesh();
    ~Mesh();
    Mesh *	asMesh(){	return this;	}

 void update();
 void destroy();

void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
void loadModel(const char *filename);
QVector<SubMesh*> submeshes;
private:
// Assimp stuff
void processNode(aiNode *node, const aiScene *scene);
SubMesh * processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif // MESH_H
