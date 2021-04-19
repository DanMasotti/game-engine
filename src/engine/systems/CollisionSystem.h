#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"
#include "unordered_map"
#include "unordered_set"

#include "../util/CommonIncludes.h"

class CollisionSystem: public System
{
public:
    CollisionSystem();

    virtual void onTick(float seconds) override;

    int point2Cell(const glm::vec3& p);

private:
    void detect();
    std::unordered_map<std::shared_ptr<GameObject>, int> m_object2Cell;
    std::unordered_map<int, std::unordered_set<std::shared_ptr<GameObject>>> m_cell2Objects;
    float m_meters2Cell;
};

#endif // COLLISIONSYSTEM_H
