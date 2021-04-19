#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "System.h"
#include "QMap"


class DrawableComponent;
class Graphics;

class DrawSystem: public System
{
public:
   DrawSystem();

   void onDraw(Graphics* g);

};

#endif // DRAWSYSTEM_H
