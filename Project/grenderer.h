#ifndef GRENDERER_H
#define GRENDERER_H

class gEditorCamera;

class gRenderer
{
public:
    gRenderer() {}
    virtual ~gRenderer() {}
    virtual void Initialize() = 0;
    virtual void Resize(int w, int h) = 0;
    virtual void Render(gEditorCamera *editorCamera) = 0;
protected:
    virtual void PassMesh(gEditorCamera *editorCamera){}
    virtual void PassMaterials(){}
    virtual void PassLights(){}
    virtual void PassSelectionOutline(){}
    virtual void PassGrid(){}

};

#endif // GRENDERER_H
