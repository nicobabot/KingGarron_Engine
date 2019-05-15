#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QListWidgetItem>
//#include "gdeferredrenderer.h"

#define DT 0.0166666666666667f

class Mesh;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
class QEvent;
class gGLInput;
class gEditorCamera;
class gObject;
class InspectorWidget;
class gDeferredRenderer;

enum RenderType{
    ALBEDO_RENDER,
    NORMAL_RENDER,
    DEPTH_RENDER
};

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget() override;
    void initializeGL();
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void UpdateMeshs();

public slots:
    void Update();
    void HierarchyAdd();
    void HierarchyRemove();
    void HierarchyClicked(QListWidgetItem* item = nullptr);
    void ChangeRenderToAlbedo();
    void ChangeRenderToNormal();
    void ChangeRenderToDepth();

private:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    void BindTypeOfRender(int forceBind = -1);

public:
    QVector<Mesh*> myMeshScene;
    QVector<gObject*> myObjectsScene;
    Mesh *myMesh = nullptr;
    bool needUpdate = false;
    gGLInput* inputClass = nullptr;
    gEditorCamera* editorCamera = nullptr;
    int objectNum = 0;
    int clickedIndex = 0;

private:
    InspectorWidget *inspectorWidget = nullptr;

    gDeferredRenderer *deferredRendering = nullptr;
    RenderType renderType = RenderType::ALBEDO_RENDER;

    QTimer timer;
    //Stuff
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram programSSAO;
};

#endif // MYOPENGLWIDGET_H
