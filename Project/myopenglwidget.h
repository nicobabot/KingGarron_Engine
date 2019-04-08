#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "gglinput.h"
#include <QTimer>

class Mesh;
class QKeyEvent;
class QMouseEvent;
class QEvent;

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

    QVector<Mesh*> myMeshScene;


    void Update();

    Mesh *myMesh = nullptr;
    QVector3D position = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D reference = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D X = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D Y = QVector3D(0.0f, 0.0f, -3.0f);
    QVector3D Z = QVector3D(0.0f, 0.0f, -3.0f);

    bool needUpdate = false;

private:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QTimer timer;
    gGLInput* inputClass = nullptr;
    //Stuff
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
};

#endif // MYOPENGLWIDGET_H
