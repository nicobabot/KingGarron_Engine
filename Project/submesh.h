#ifndef SUBMESH_H
#define SUBMESH_H

#include"vertexformat.h"
#include<QtOpenGL>

class SubMesh
{
public:
    SubMesh(QString name, VertexFormat vertexFormat,	void *data, int	size);
    SubMesh(QString name, VertexFormat vertexFormat,	void *data, int	size, unsigned int *indices, int indices_count);
    ~SubMesh();

    void update();
    void draw();
    void destroy();

public:

    QOpenGLTexture *textureOpenGL = nullptr;
    QString name = "none";

private:
    unsigned char *data = nullptr;
    size_t data_size = 0;
    unsigned int *indices = nullptr;
    size_t indices_count = 0;

    VertexFormat vertexFormat;

    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;

    QOpenGLFunctions *glfuncs = nullptr;
};
#endif // SUBMESH_H
