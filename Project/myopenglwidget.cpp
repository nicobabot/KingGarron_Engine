#include "myopenglwidget.h"
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "mesh.h"
#include "submesh.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>
#include "gglinput.h"
#include "geditorcamera.h"
#include <gobject.h>
#include <gcomponentrender.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gcomponenttransform.h"
#include "inspectorwidget.h"

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
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/shaderl_frag.fsh");
    program.link();

    // VB0

    //glDisable(GL_CULL_FACE);

}

void MyOpenGLWidget::resizeGL(int width, int height)
{

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QVector3D vertices[] = { QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f),
                             QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f),
                             QVector3D( 0.0f, 0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f) };

    QMatrix4x4 view;
    view.setToIdentity();
    view.setColumn(0, QVector4D(editorCamera->X,0));
    view.setColumn(1, QVector4D(editorCamera->Y,0));
    view.setColumn(2, QVector4D(editorCamera->Z,0));
    view.setColumn(3, QVector4D(editorCamera->position,1));
    QMatrix4x4 proj;
    proj.setToIdentity();
    proj.perspective(90.0f, static_cast<float>(width()) / static_cast<float>(height()), 0.1f, 100.0f);

    program.bind();

    int projecLoc = glGetUniformLocation(program.programId(), "projection");
    glUniformMatrix4fv(projecLoc, 1, GL_TRUE, proj.transposed().data());

    int viewLoc = glGetUniformLocation(program.programId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.transposed().data());


    //QMatrix4x4 mvp = (proj * view * model);
    //mvp = mvp.transposed();    

 if(!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));
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
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesO));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytesl));



    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0,3);
    }

    // Release
    vao.release();
    vbo.release();



    if(needUpdate)
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

        if(render->textureOpenGL!=nullptr)
        {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, render->textureOpenGL->textureId());
        //int texturePos = glGetUniformLocation(program.programId(), "ourTexture");
        //glUniform1i(texturePos, render->textureOpenGL->textureId());

        //qDebug("Texture pos: %i, and texture id: %i", texturePos, render->textureOpenGL->textureId());

        //render->textureOpenGL->bind();
        }
        render->Render();
    }
    program. release();
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
    inputClass->Update();
    editorCamera->Update();
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
