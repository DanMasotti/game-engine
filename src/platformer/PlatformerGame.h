#ifndef PLATFORMERGAME_H
#define PLATFORMERGAME_H

#include "engine/Application.h"

namespace Platformer {
class PlatformerGame: public Application
{
public:
    PlatformerGame();

    virtual void reset(int gameState) override;
};
}



#endif // PLATFORMERGAME_H
