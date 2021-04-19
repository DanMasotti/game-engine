#ifndef PLATFORMERGAMESCREEN_H
#define PLATFORMERGAMESCREEN_H

#include "engine/Screen.h"

namespace Platformer {
class GameScreen: public Screen
{
public:
    GameScreen(Application* app, std::shared_ptr<Camera> cam);


    void loadAnimations();


};
}


#endif // PLATFORMERGAMESCREEN_H
