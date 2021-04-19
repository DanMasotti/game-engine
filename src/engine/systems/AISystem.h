#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "System.h"
#include "../graphics/obj.h"
#include "../ai/Graph.h"

class Blackboard;
class GameWorld;

class AISystem: public System
{
public:
    AISystem(QString filepath, GameWorld* world);

    virtual void onTick(float seconds) override;

    std::shared_ptr<Blackboard> getBlackboard() const;

private:
    GameWorld* m_world;
    std::shared_ptr<Blackboard> m_blackboard;
};

#endif // AISYSTEM_H
