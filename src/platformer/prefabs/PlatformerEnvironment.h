#ifndef PLATFORMERENVIRONMENT_H
#define PLATFORMERENVIRONMENT_H

#include "engine/GameObject.h"

namespace Platformer {
class Environment: public GameObject
{
public:
    Environment(GameWorld* world, QString id);
};
}


#endif // PLATFORMERENVIRONMENT_H
