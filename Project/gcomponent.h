#ifndef GCOMPONENT_H
#define GCOMPONENT_H

class gObject;

enum gComponentType{
    COMP_UNDEFINED,
    COMP_TRANSFORM,
    COMP_RENDER
};

class gComponent
{
public:
    gComponent(gObject *parent = nullptr);
public:
    gObject *parent = nullptr;
    gComponentType compType = gComponentType::COMP_UNDEFINED;
};

#endif // GCOMPONENT_H
