#ifndef PLAYER_H
#define PLAYER_H

#include "engine/GameObject.h"


namespace Platformer {
class Player: public GameObject
{
public:
    Player(GameWorld* world);
};
}


#endif // PLAYER_H
