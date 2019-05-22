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
    //saoRendering

  /*  QVector3D vertices[] = { QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), //QVector3D(0.0f, 0.0f, 0.0f),
                             QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), //QVector3D(1.0f, 0.0f, 0.0f),
                             QVector3D( 0.0f, 0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)}; //QVector3D(0.0f, 1.0f, 0.0f)};
*/

    /*std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;
    //std::vector<glm::vec3> ssaoKernel;
   // QVector<QVector3D> ssaoKernel;
    float ssaoKernel[64 * 3];

    for (unsigned int i = 0; i < 192; i+=3)
    {
     QVector3D sample(
     randomFloats(generator) * 2.0 - 1.0,
     randomFloats(generator) * 2.0 - 1.0,
     randomFloats(generator)
     );
     sample.normalize();
     sample *= randomFloats(generator);
     float scale = (float)i / 192.0;

     //LERP
     //scale = lerp(0.1f, 1.0f, scale * scale);
     scale = 0.1f + (scale * scale) * (1.0f - 0.1f);

     sample *= scale;
     ssaoKernel[i]=sample.x();
     ssaoKernel[i+1]=sample.y();
     ssaoKernel[i+2]=sample.z();
    }
*/

    /*if(program.bind())
    {
        program.setUniformValue("typeOfRender",1);
        program.setUniformValue("viewport_size",QVector2D(width(), height()));
        program.setUniformValue("viewMatInv",editorCamera->viewMatrix.inverted());
        program.setUniformValue("projMatInv",editorCamera->projMatrix.inverted());
        program.setUniformValue("cameraPos",editorCamera->position);

        program.setUniformValue(program.uniformLocation("ourTexture"), 0);
        program.setUniformValue(program.uniformLocation("normalMap"), 1);
        program.setUniformValue(program.uniformLocation("depthMap"), 2);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deferredRendering->GetNormalTexture());
        //BindTypeOfRender();

        glActiveTexture(GL_TEXTURE1);
        BindTypeOfRender(1);

        glActiveTexture(GL_TEXTURE2);
        BindTypeOfRender(2);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,6);
    }

    // Release
    vao.release();
    vbo.release();
    program.release();
    glBindTexture(GL_TEXTURE_2D, 0);*/

}

void MyOpenGLWidget::BindTypeOfRender(int forceBind)
{
    RenderType typeToRender;
    if(forceBind!=-1) typeToRender = (RenderType)forceBind;
    else typeToRender = renderType;

    switch (typeToRender)
    {
        case RenderType::ALBEDO_RENDER:
               glBindTexture(GL_TEXTURE_2D, deferredRendering->GetColorTexture());
        break;
        case RenderType::NORMAL_RENDER:
               //qDebug("Normal texture: %i",deferredRendering->GetNormalTexture());
               glBindTexture(GL_TEXTURE_2D, deferredRendering->GetNormalTexture());
        break;
        case RenderType::DEPTH_RENDER:
               glBindTexture(GL_TEXTURE_2D, deferredRendering->GetDepthTexture());
        break;
    }
}

void MyOpenGLWidget::ChangeRenderToAlbedo()
{
    renderType = RenderType::ALBEDO_RENDER;
}

void MyOpenGLWidget::ChangeRenderToNormal()
{
    renderType = RenderType::NORMAL_RENDER;
}
void MyOpenGLWidget::ChangeRenderToDepth()
{
    renderType = RenderType::DEPTH_RENDER;
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
