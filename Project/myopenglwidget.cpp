#include "myopenglwidget.h"
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "mesh.h"
#include "submesh.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QEvent>
#include "gglinput.h"
#include "geditorcamera.h"
#include <gobject.h>
#include <gcomponentrender.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gcomponenttransform.h"
#include "inspectorwidget.h"
#include "gdeferredrenderer.h"
#include "gsaorender.h"
#include "grenderlight.h"

#pragma comment(lib, "OpenGL32.lib")

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setFocus();
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    inputClass = new gGLInput();
    editorCamera = new gEditorCamera();

    inspectorWidget = new InspectorWidget();
    mainWindow->Inspector->setWidget(inspectorWidget);

    connect(mainWindow->HierarchyAdd, SIGNAL(clicked()), this, SLOT(HierarchyAdd()));
    connect(mainWindow->HierarchyRemove, SIGNAL(clicked()), this, SLOT(HierarchyRemove()));
    connect(mainWindow->HierarchyList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(HierarchyClicked(QListWidgetItem*)));

    //connect(mainWindow->mainToolBar, SIGNAL(triggered(QAction *action)), this,SLOT(ChangeRenderType(QAction *action)));

    connect(mainWindow->actionAlbedo, &QAction::triggered, this, &MyOpenGLWidget::ChangeRenderToAlbedo);
    connect(mainWindow->actionNormal, &QAction::triggered, this, &MyOpenGLWidget::ChangeRenderToNormal);
    connect(mainWindow->actionDepth, &QAction::triggered, this, &MyOpenGLWidget::ChangeRenderToDepth);
    connect(mainWindow->actionSSAO, &QAction::triggered, this, &MyOpenGLWidget::ChangeRenderToSSAO);
    connect(mainWindow->actionLight, &QAction::triggered, this, &MyOpenGLWidget::ChangeRenderToLightMap);

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(Update()));

    if (format().swapInterval() == -1)
        timer.setInterval(17);
    else
        timer.setInterval(0);
    timer.start();

    this->setUpdatesEnabled(true);
    this->setMouseTracking(true);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    delete inputClass;
    delete editorCamera;
    makeCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    /*Mesh* objMesh = new Mesh();
    objMesh->loadModel("D:/CITM/4rto/Prog Grafica/KingGarron/KingGarron_Engine/Project/Models/Patrick/Patrick.obj");

    myMeshScene.push_back(objMesh);

    //UpdateMeshs();

    needUpdate = true;*/

    static bool onetime = true;
    if (onetime)
    {
        onetime=false;
        program.create();
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert_copy.vsh");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag_copy.fsh");
        program.link();

        programSSAO.create();
        programSSAO.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/ssao_vertexshader.vsh");
        programSSAO.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/ssao_fragmentshader.fsh");
        programSSAO.link();

        deferredRendering = new gDeferredRenderer(width(), height());
        deferredRendering->Initialize();

        saoRendering = new gSaoRender(width(), height());
        saoRendering->Initialize();
        saoRendering->SetDeferredRender(deferredRendering);

        lightRendering = new gRenderLight(width(), height());
        lightRendering->Initialize();
        lightRendering->SetDeferredRender(deferredRendering);
        lightRendering->SetSSAORender(saoRendering);

    }


    float verticesQuad[] = {     /*Position*/-1.0f, -1.0f, 0.0f, /*Color*/ 1.0f, 1.0f, 1.0f,  /*TextureCoord*/ 0.0f, 0.0f,
                                              1.0f, 1.0f, 0.0f,            1.0f, 1.0f, 1.0f,                   1.0f, 1.0f,
                                              -1.0f, 1.0f, 0.0f,           1.0f, 1.0f, 1.0f,                   0.0f, 1.0f,
                                              -1.0f, -1.0f, 0.0f,          1.0f, 1.0f, 1.0f,                   0.0f, 0.0f,
                                               1.0f, -1.0f, 0.0f,          1.0f, 1.0f, 1.0f,                   1.0f, 0.0f,
                                               1.0f, 1.0f, 0.0f,           1.0f, 1.0f, 1.0f,                   1.0f, 1.0f };

 program.bind();

 if(!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(verticesQuad, 49 * sizeof(float));
    // VAO: Captures state of VBOs
    if(!vao.isCreated())
        vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 8 * sizeof(float);
    const int offsetBytesO = 0;
    const int offsetBytesl = sizeof(float)*3;
    const int offsetBytes2 = sizeof(float)*6;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesO));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl));
    glVertexAttribPointer(2, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes2));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    deferredRendering->Resize(width, height);
    saoRendering->Resize(width, height);
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    deferredRendering->Render(editorCamera);
    saoRendering->Render(editorCamera);
    lightRendering->Render(editorCamera);

    if(inputClass->GetKeyIsState(Qt::Key_R, KEY_STATE::KEY_DOWN))
    {
        lightRendering->ReloadShaders();
    }

}

void MyOpenGLWidget::ReloadObjShaders()
{
    for(gObject* myObject : myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

        gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

        if(render!=nullptr)
                render->ReloadMyShader();

    }
}

void MyOpenGLWidget::ChangeRenderToAlbedo()
{
    lightRendering->renderType = RenderType::ALBEDO_RENDER;
}

void MyOpenGLWidget::ChangeRenderToNormal()
{
    lightRendering->renderType = RenderType::NORMAL_RENDER;
}
void MyOpenGLWidget::ChangeRenderToDepth()
{
    lightRendering->renderType = RenderType::DEPTH_RENDER;
}
void MyOpenGLWidget::ChangeRenderToSSAO()
{
    lightRendering->renderType = RenderType::SSAO_RENDER;
}

void MyOpenGLWidget::ChangeRenderToLightMap()
{
    lightRendering->renderType = RenderType::LIGHT_RENDER;
}

void MyOpenGLWidget::UpdateMeshs()
{
    for(gObject* myObject : myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

           gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

         if(render==nullptr)
             continue;

         render->Update();

    }
}

void MyOpenGLWidget::HierarchyAdd()
{
    std::string name = "Object_";
    name += std::to_string(objectNum++);
    mainWindow->HierarchyList->addItem(QString(name.c_str()));
    myObjectsScene.append(new gObject(QString(name.c_str()), true));
    this->repaint();
}

void MyOpenGLWidget::HierarchyRemove()
{
    QModelIndexList indexes = mainWindow->HierarchyList->selectionModel()->selectedIndexes();
    std::vector<int> indexList;
    for(QModelIndex index : indexes)
        indexList.push_back(index.row());
    for (int i = 0; i < static_cast<int>(indexList.size()); i++)
    {
        delete myObjectsScene.at(indexList.at(i));
            myObjectsScene.remove(indexList.at(i));
    }
    qDeleteAll(mainWindow->HierarchyList->selectedItems());
    HierarchyClicked();
    this->repaint();
}

void MyOpenGLWidget::HierarchyClicked(QListWidgetItem* item)
{
    QModelIndexList indexes = mainWindow->HierarchyList->selectionModel()->selectedIndexes();
    if (indexes.size() == 0)
        clickedIndex = -1;
    else
        clickedIndex = indexes[0].row();
    if (clickedIndex >= 0)
        inspectorWidget->UpdateInspectorValues(myObjectsScene.at(clickedIndex));
    else
        inspectorWidget->UpdateInspectorValues(nullptr);
    //qDebug("index: %i", clickedIndex);
}

void MyOpenGLWidget::Update()
{
    editorCamera->Update();
    editorCamera->CalcWorldViewMatrices();
    editorCamera->CalcProjMatrix(width(), height());
    inputClass->Update(); //keep input at the bottom
    //ReloadObjShaders();
    //mainWindow->Scene_2->setFloating(false);
    this->update();
    //this->repaint();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    inputClass->keyPressEvent(event);
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    inputClass->keyReleaseEvent(event);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->mousePressEvent(event);
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->mouseMoveEvent(event);
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->mouseReleaseEvent(event);
}

void MyOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->wheelEvent(event);
}

void MyOpenGLWidget::enterEvent(QEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->enterEvent(event);
}

void MyOpenGLWidget::leaveEvent(QEvent* event)
{
    //if (event->isAutoRepeat()) return;
    inputClass->leaveEvent(event);
}
