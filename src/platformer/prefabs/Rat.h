#ifndef RAT_H
#define RAT_H

#include "engine/GameObject.h"

namespace Platformer {
class Rat: public GameObject
{
public:
    Rat(GameWorld* world, QString id, glm::vec3 position);
};
}


#endif // RAT_H
