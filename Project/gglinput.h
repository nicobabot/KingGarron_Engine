#ifndef GGLINPUT_H
#define GGLINPUT_H

class QKeyEvent;
class QMouseEvent;
class QEvent;
class MyOpenGLWidget;

#define MAX_BUTTONS 10
#define MAX_KEYS 300

enum KEY_STATE
{
    KEY_IDLE = 0,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};

class gGLInput
{
public:
    gGLInput();
    void Update();

    KEY_STATE GetKey(int id) const;
    KEY_STATE GetMouseButton(int id) const;
    int GetMouseX() const;
    int GetMouseY() const;
    int GetMouseZ() const;
    int GetMouseXMotion() const;
    int GetMouseYMotion() const;

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    KEY_STATE keyboard[MAX_KEYS];
    KEY_STATE keyboardOld[MAX_KEYS];
    KEY_STATE mouse_buttons[MAX_BUTTONS];
    int mouse_x = 0;
    int mouse_y = 0;
    int mouse_z = 0;
    int mouse_x_motion = 0;
    int mouse_y_motion = 0;
};

#endif // GGLINPUT_H