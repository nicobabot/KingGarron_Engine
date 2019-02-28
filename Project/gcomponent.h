#ifndef GCOMPONENT_H
#define GCOMPONENT_H

class gObject;

class gComponent
{
public:
    gComponent(gObject *parent = nullptr);
public:
    gObject *parent = nullptr;
};

#endif // GCOMPONENT_H
