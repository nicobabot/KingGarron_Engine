#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include<QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget() override;
    void initializeGL();
    void resizeGL(int width, int height) override;
    void paintGL() override;
private:
    void keyPressEvent(QKeyEvent*);
};

#endif // MYOPENGLWIDGET_H
