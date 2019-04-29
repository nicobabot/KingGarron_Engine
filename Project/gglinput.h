#ifndef GGLINPUT_H
#define GGLINPUT_H

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
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
    ~gGLInput();
    void Update();

    KEY_STATE GetKey(int id) const;
    bool GetKeyIsState(int id, KEY_STATE state) const;
    KEY_STATE GetMouseButton(int id) const;
    bool GetMouseButtonIsState(int id, KEY_STATE state) const;
    int GetMouseX() const;
    int GetMouseY() const;
    int GetMouseXMotion() const;
    int GetMouseYMotion() const;

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    KEY_STATE* keyboard = nullptr;
    KEY_STATE* keyboardOld = nullptr;
    KEY_STATE* mouse_buttons = nullptr;
    KEY_STATE* mouse_buttonsOld = nullptr;
    int mouse_x = 0;
    int mouse_y = 0;
    int mouse_x_motion = 0;
    int mouse_y_motion = 0;
};

#endif // GGLINPUT_H
