#ifndef GRENDERER_H
#define GRENDERER_H

class gRenderer
{
public:
    gRenderer() {}
    virtual ~gRenderer() {}
    virtual void Initialize() = 0;
    virtual void Resize(int w, int h) = 0;
    virtual void Render() = 0;
protected:
    virtual void PassMaterials() = 0;
    virtual void PassLights() = 0;
    virtual void PassSelectionOutline() = 0;
    virtual void PassGrid() = 0;

};

#endif // GRENDERER_H
