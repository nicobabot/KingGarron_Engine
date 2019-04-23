#ifndef GDEFERREDRENDERER_H
#define GDEFERREDRENDERER_H

#include "grenderer.h"

class gDeferredRenderer : gRenderer
{
public:
    gDeferredRenderer();
    ~gDeferredRenderer();
    void initialize();
    void resize(int w, int h);
    void render();
private:
    void PassMaterials();
    void PassLights();
    void PassSelectionOutline();
    void PassGrid();
};

#endif // GDEFERREDRENDERER_H
