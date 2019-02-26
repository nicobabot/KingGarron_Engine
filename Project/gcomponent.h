#ifndef GCOMPONENT_H
#define GCOMPONENT_H

class QWidget;
class gObject;

class gComponent
{
    Q_OBJECT
public:
    gComponent(gObject *parent = nullptr);
public:
    gObject *parent = nullptr;
};

#endif // GCOMPONENT_H
