#ifndef ENVIRONMENTCOLLISIONCOMPONENT_H
#define ENVIRONMENTCOLLISIONCOMPONENT_H

#include "engine/graphics/obj.h"
#include "Component.h"

class EnvironmentCollisionComponent: public Component
{
public:
    EnvironmentCollisionComponent(GameObject* object, glm::vec3 radius);

    std::pair<std::vector<CollisionData>, glm::vec3>  ellipsoidTriangleCollisions(const glm::vec3& start,
                                                                                  const glm::vec3& end,
                                                                                  const QList<OBJ::Triangle*>& triangles) const;
    std::shared_ptr<CollisionEllipsoid> getEllipsoid() const;

private:

    CollisionData ellipsoidIntersectTriangle(const glm::vec3& ellipsoidStart, const glm::vec3& ellipsoidEnd, OBJ::Triangle* triangle) const;
    CollisionData getClosestCollision(const glm::vec3& currPos, const glm::vec3& nextPos, const QList<OBJ::Triangle*>& triangles) const;
    glm::vec3 doNudge(const glm::vec3& currPos, CollisionData c, const QList<OBJ::Triangle*>& triangles) const;

    std::shared_ptr<CollisionEllipsoid> m_ellipsoid;
};

#endif // ENVIRONMENTCOLLISIONCOMPONENT_H
