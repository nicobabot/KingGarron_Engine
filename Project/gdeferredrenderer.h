#ifndef GDEFERREDRENDERER_H
#define GDEFERREDRENDERER_H

#include "grenderer.h"

class gDeferredRenderer : gRenderer
{
public:
    gDeferredRenderer();
    ~gDeferredRenderer();
    void Initialize();
    void Resize(int w, int h);
    void Render();
private:
    void PassMesh();
    void PassMaterials();
    void PassLights();
    void PassSelectionOutline();
    void PassGrid();
};

#endif // GDEFERREDRENDERER_H
