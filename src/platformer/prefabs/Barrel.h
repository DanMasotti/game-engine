#ifndef BARREL_H
#define BARREL_H

#include "engine/GameObject.h"

namespace Platformer {
class Barrel: public GameObject
{
public:
    Barrel(GameWorld* world, QString id, glm::vec3 position);
};
}

#endif // BARREL_H
