#include "submesh.h"
#include<QtOpenGL>
#include<QOpenGLFunctions_3_3_Core>
#include<QMatrix4x4>

SubMesh::SubMesh(VertexFormat vertexFormat,	void *data, int	size)
{
    this->vertexFormat = vertexFormat;
    this->data = static_cast<unsigned char*>(data);
    this->data_size = size;
    glfuncs = QOpenGLContext::currentContext()->functions();
}
SubMesh::SubMesh(VertexFormat vertexFormat,	void *data, int	size, unsigned int *indices, int indices_count)
{
    this->vertexFormat = vertexFormat;
    this->data = static_cast<unsigned char*>(data);
    this->data_size = size;
    this->indices = indices;
    this->indices_count = indices_count;
    glfuncs = QOpenGLContext::currentContext()->functions();
}
SubMesh::~SubMesh()
{

}
void SubMesh::update()
{
    //glLoadMatrixf()

    glTranslatef(0,0, -5);
    glPushMatrix();
    glLoadIdentity();

    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.translate(QVector3D(0.0f, 0.0f, 0.0f));
    mat.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));

    //glRotatef()

    // VAO: Vertex format description and state of VBOs vao.create();
    vao.bind();
    // VBO: Buffer with vertex data
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data, int(data_size));
    delete[] data;
    data = nullptr;
    // IBO: Buffer with indexes if (indices != nullptr)
    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw); ibo.allocate(indices, int(indices_count * sizeof(unsigned int))); delete[] indices;
    indices = nullptr;
    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES; ++location)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];
        if (attr.enabled)
        {

            glfuncs->glEnableVertexAttribArray(GLuint(location));
            glfuncs->glVertexAttribPointer(GLuint(location), attr.ncomp,GL_FLOAT,GL_FALSE,vertexFormat.size, (void *)(attr.offset));
        }
    }
    // Release
    vao.release();
    vbo.release();
    if (ibo.isCreated()) {
    ibo.release();
    }

    glPopMatrix();

}
void SubMesh::draw()
{
    int num_vertices = data_size / vertexFormat.size;
    vao.bind();
    if (indices_count > 0) {
    glfuncs->glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
    }
    else {
    glfuncs->glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    vao.release();
}
void SubMesh::destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}
