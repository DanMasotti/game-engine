#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "System.h"

class Graphics;

class UISystem: public System
{
public:
    UISystem();

    void onDraw(Graphics* g);
};

#endif // UISYSTEM_H
