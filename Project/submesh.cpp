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
    //this->data = static_cast<unsigned char*>(data);
    this->data = new unsigned char[size];
    std::memcpy(this->data, data, size);
    this->data_size = size;
    this->indices_count = indices_count;
    this->indices = new unsigned int[indices_count];
    std::memcpy(this->indices, indices, indices_count * sizeof(unsigned int));
    glfuncs = QOpenGLContext::currentContext()->functions();
}
SubMesh::~SubMesh()
{

}
void SubMesh::update()
{
    //glLoadMatrixf()

    //glTranslatef(0,0, -5);
    //glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*QMatrix4x4 mat;
    mat.setToIdentity();
    mat.translate(QVector3D(0.0f, 0.0f, 0.0f));
    mat.rotate(0.0f, QVector3D(0.0f, 1.0f, 0.0f));*/

    //glRotatef()
    qDebug("1");

    // VAO: Vertex format description and state of VBOs vao.create();
    vao.bind();
    // VBO: Buffer with vertex data
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data, int(data_size));
    qDebug("2");
    //delete[] data;
    qDebug("3");
    data = nullptr;
    qDebug("4");
    // IBO: Buffer with indexes if (indices != nullptr)
    ibo.create();
    qDebug("5");
    ibo.bind();
    qDebug("6");
    ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);

    qDebug("MY INDICES ARE %i", indices_count);

    ibo.allocate(indices, int(indices_count * sizeof(unsigned int)));
    //delete[] indices;
    qDebug("7");
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

    //glPopMatrix();

}
void SubMesh::draw()
{
    qDebug("8");
    int num_vertices = data_size / vertexFormat.size;
    qDebug("9");
    vao.bind();
    if (indices_count > 0) {
        qDebug("10");
    glfuncs->glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
        qDebug("10.5");
    }
    else {
        qDebug("11");
    glfuncs->glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    qDebug("12");
    vao.release();
}
void SubMesh::destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}
