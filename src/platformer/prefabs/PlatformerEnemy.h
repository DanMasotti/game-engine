#ifndef PLATFORMERENEMY_H
#define PLATFORMERENEMY_H

#include "engine/GameObject.h"

namespace Platformer {
class Enemy: public GameObject
{
public:
    Enemy(GameWorld* world, QString id, glm::vec3 position);
};
}

#endif // PLATFORMERENEMY_H
