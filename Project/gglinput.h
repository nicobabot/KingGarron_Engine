#ifndef GGLINPUT_H
#define GGLINPUT_H

class QKeyEvent;
class QMouseEvent;
class QEvent;

class gGLInput
{
public:
    gGLInput();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
};

#endif // GGLINPUT_H
