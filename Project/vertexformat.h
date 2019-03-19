#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

static const int MAX_VERTEX_ATTRIBUTES = 3;

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:
    VertexFormat();

    void setVertexAttribute(int location, int offset, int ncomp)
    {
        attribute[location].enabled = true;
        attribute[location].offset = offset;
        attribute[location].ncomp = ncomp;
        size += ncomp * sizeof(float);
    }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

#endif // VERTEXFORMAT_H
