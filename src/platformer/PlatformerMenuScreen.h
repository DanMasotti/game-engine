#ifndef PLATFORMERMENUSCREEN_H
#define PLATFORMERMENUSCREEN_H

#include "engine/Screen.h"


class Application;
class Camera;

namespace Platformer {

class MenuScreen: public Screen
{
public:
    MenuScreen(Application* app, std::shared_ptr<Camera> cam);

};
}




#endif // PLATFORMERMENUSCREEN_H
