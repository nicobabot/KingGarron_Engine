#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include<QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class Mesh;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget() override;
    void initializeGL();
    void resizeGL(int width, int height) override;
    void paintGL() override;

      Mesh *myMesh = nullptr;

};

#endif // MYOPENGLWIDGET_H
