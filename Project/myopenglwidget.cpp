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

    // Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/shaderl_vert.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag_copy.fsh");
    program.link();


    deferredRendering = new gDeferredRenderer(width(), height());
    deferredRendering->Initialize();

    glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    deferredRendering->Render(editorCamera);

    QVector3D vertices[] = { QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), //QVector3D(0.0f, 0.0f, 0.0f),
                             QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), //QVector3D(1.0f, 0.0f, 0.0f),
                             QVector3D( 0.0f, 0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)}; //QVector3D(0.0f, 1.0f, 0.0f)};

    QVector3D verticesQuad[] = {     QVector3D(-0.5f, -0.5f, 0.0f),  QVector3D(1.0f, 0.0f, 0.0f),   QVector3D(0.0f, 0.0f, 0.0f),
                                     QVector3D(0.5f, 0.5f, 0.0f),   QVector3D(1.0f, 0.0f, 0.0f),    QVector3D(1.0f, 1.0f, 0.0f),
                                     QVector3D(-0.5f, 0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f),     QVector3D(0.0f, 1.0f, 0.0f),
                                     QVector3D(-0.5f, -0.5f, 0.0f),  QVector3D(1.0f, 0.0f, 0.0f),   QVector3D(0.0f, 0.0f, 0.0f),
                                     QVector3D(0.5f, -0.5f, 0.0f),  QVector3D(1.0f, 0.0f, 0.0f),    QVector3D(1.0f, 0.0f, 0.0f),
                                     QVector3D(0.5f, 0.5f, 0.0f),  QVector3D(1.0f, 0.0f, 0.0f),    QVector3D(1.0f, 1.0f, 0.0f) };

    program.bind();

    int projecLoc = glGetUniformLocation(program.programId(), "projection");
    glUniformMatrix4fv(projecLoc, 1, GL_TRUE, editorCamera->projMatrix.transposed().data());

    int viewLoc = glGetUniformLocation(program.programId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, editorCamera->viewMatrix.transposed().data());

    QMatrix4x4 matrix;
    matrix.setToIdentity();

    int modelLoc = glGetUniformLocation(program.programId(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, matrix.data());

    //QMatrix4x4 mvp = (proj * view * model);
    //mvp = mvp.transposed();

 if(!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(verticesQuad, 18 * sizeof(QVector3D));
    // VAO: Captures state of VBOs
    if(!vao.isCreated())
        vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytesO = 0;
    const int offsetBytesl = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesO));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl));
    glVertexAttribPointer(2, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl*2));


    if(program.bind())
    {
        program.setUniformValue(program.uniformLocation("ourTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deferredRendering->colorTexture);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,6);
    }

    // Release
    vao.release();
    vbo.release();
    program.release();
    glBindTexture(GL_TEXTURE_2D, 0);

    /*if(needUpdate)
    {
        qDebug("UPDATE MESH");
        UpdateMeshs();
        needUpdate = false;
    }

    for(gObject* myObject : myObjectsScene)
    {
        if(myObject==nullptr)
            continue;

        gComponentTransform *trans = (gComponentTransform*)myObject->GetComponent(gComponentType::COMP_TRANSFORM);

        QVector3D position = trans->position;

        float rotx, roty, rotz;
        trans->rotation.getEulerAngles(&rotx, &roty, &rotz);

        QVector3D scale = trans->scale;
        QMatrix4x4 model;
        model.translate(QVector3D(position.x(), position.y(), position.z()));
        model.rotate(trans->rotation);
        model.scale(QVector3D(scale.x(), scale.y(), scale.z()));

        int modelLoc = glGetUniformLocation(program.programId(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.transposed().data());

        gComponentRender *render = (gComponentRender*)myObject->GetComponent(gComponentType::COMP_RENDER);

        glActiveTexture(GL_TEXTURE0);
        render->Render();
    }
    program. release();*/




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
