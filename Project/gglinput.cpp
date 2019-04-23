#include "gglinput.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>

gGLInput::gGLInput()
{
    keyboard = new KEY_STATE[MAX_KEYS];
    keyboardOld = new KEY_STATE[MAX_KEYS];
    mouse_buttons = new KEY_STATE[MAX_BUTTONS];
    mouse_buttonsOld = new KEY_STATE[MAX_BUTTONS];
    memset(keyboard, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    memset(keyboardOld, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    memset(mouse_buttons, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_BUTTONS);
    memset(mouse_buttonsOld, KEY_STATE::KEY_IDLE, sizeof(KEY_STATE) * MAX_BUTTONS);
}

gGLInput::~gGLInput()
{
    delete[] keyboard;
    delete[] keyboardOld;
    delete[] mouse_buttons;
    delete[] mouse_buttonsOld;
}

void gGLInput::Update()
{
    for(int id = 0; id < MAX_KEYS; id++)
        if (keyboardOld[id] == keyboard[id])
        {
            if (keyboardOld[id] == KEY_STATE::KEY_DOWN && keyboard[id] == KEY_STATE::KEY_DOWN) keyboard[id] = KEY_STATE::KEY_REPEAT;
            if (keyboardOld[id] == KEY_STATE::KEY_UP && keyboard[id] == KEY_STATE::KEY_UP) keyboard[id] = KEY_STATE::KEY_IDLE;
        }
    memcpy(keyboardOld, keyboard, sizeof(KEY_STATE) * MAX_KEYS);
    for(int id = 0; id < MAX_BUTTONS; id++)
        if (mouse_buttonsOld[id] == mouse_buttons[id])
        {
            if (mouse_buttonsOld[id] == KEY_STATE::KEY_DOWN && mouse_buttons[id] == KEY_STATE::KEY_DOWN) mouse_buttons[id] = KEY_STATE::KEY_REPEAT;
            if (mouse_buttonsOld[id] == KEY_STATE::KEY_UP && mouse_buttons[id] == KEY_STATE::KEY_UP) mouse_buttons[id] = KEY_STATE::KEY_IDLE;
        }
    memcpy(mouse_buttonsOld, mouse_buttons, sizeof(KEY_STATE) * MAX_BUTTONS);
}

KEY_STATE gGLInput::GetKey(int id) const
{
    return keyboard[id];
}

bool gGLInput::GetKeyIsState(int id, KEY_STATE state) const
{
    return keyboard[id] == state;
}

KEY_STATE gGLInput::GetMouseButton(int id) const
{
    return mouse_buttons[id];
}

bool gGLInput::GetMouseButtonIsState(int id, KEY_STATE state) const
{
    return mouse_buttons[id] == state;
}

int gGLInput::GetMouseX() const
{
    return mouse_x;
}

int gGLInput::GetMouseY() const
{
    return mouse_y;
}

int gGLInput::GetMouseXMotion() const
{
    return mouse_x_motion;
}

int gGLInput::GetMouseYMotion() const
{
    return mouse_y_motion;
}

void gGLInput::keyPressEvent(QKeyEvent* event)
{
    keyboard[event->key()] = KEY_STATE::KEY_DOWN;
}

void gGLInput::keyReleaseEvent(QKeyEvent* event)
{
    keyboard[event->key()] = KEY_STATE::KEY_UP;
}

void gGLInput::mousePressEvent(QMouseEvent* event)
{
    mouse_buttons[event->button()] = KEY_STATE::KEY_DOWN;
}

void gGLInput::mouseMoveEvent(QMouseEvent* event)
{
    mouse_x_motion = event->x() - mouse_x;
    mouse_y_motion = event->y() - mouse_y;
    mouse_x = event->x();
    mouse_y = event->y();
    //qDebug("MOVE, mouse_x_motion = %.2f, mouse_y_motion = %.2f, mouse_x = %.2f, mouse_y = %.2f", mouse_x_motion, mouse_y_motion, mouse_x, mouse_y);
}

void gGLInput::mouseReleaseEvent(QMouseEvent* event)
{
    mouse_buttons[event->button()] = KEY_STATE::KEY_UP;
}

void gGLInput::enterEvent(QEvent* event)
{

}

void gGLInput::leaveEvent(QEvent* event)
{

}
