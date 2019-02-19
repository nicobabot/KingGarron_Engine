#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include<QOpenGLWidget>

class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:

    explicit MyOpenGLWidget(QWidget* parent = nullptr);

    void initializeGL();
    void resizeGL(int width, int height) override;
    void paintGL() override;

signals:

public slots:

};

#endif // MYOPENGLWIDGET_H
