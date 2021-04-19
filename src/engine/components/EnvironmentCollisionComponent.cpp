#include "EnvironmentCollisionComponent.h"
#include "engine/physics/CollisionUtils.h"
#include "engine/components/TransformComponent.h"

#define EPS 0.000001f
#define INF 100000.f


using namespace CollisionUtils;

EnvironmentCollisionComponent::EnvironmentCollisionComponent(GameObject* object, glm::vec3 radius):
    Component(object),
    m_ellipsoid(std::make_shared<CollisionEllipsoid>(radius))
{

}

CollisionData EnvironmentCollisionComponent::ellipsoidIntersectTriangle(const glm::vec3& ellipsoidStart,
                                                                        const glm::vec3& ellipsoidEnd,
                                                                        OBJ::Triangle* triangle) const {

    glm::vec3 R = m_ellipsoid->radius;

    const glm::mat4 I =glm::mat4({
                                     1.f, 0.f, 0.f, 0.f,
                                     0.f, 1.f, 0.f, 0.f,
                                     0.f, 0.f, 1.f, 0.f,
                                     0.f, 0.f, 0.f, 1.f
                                 });

    glm::mat4 ellipsoid2Sphere = I;
    ellipsoid2Sphere = glm::scale(ellipsoid2Sphere, 1.f/R);
    ellipsoid2Sphere = glm::translate(ellipsoid2Sphere, -ellipsoidStart);
    const glm::mat4 sphere2Ellipsoid = glm::inverse(ellipsoid2Sphere);

    glm::mat4 normalTransform = I;
    normalTransform = glm::scale(normalTransform, R);

    const glm::vec3 n = triangle->normal;

    const glm::vec3 A = glm::vec3(ellipsoid2Sphere*glm::vec4(triangle->vertices[0], 1));
    const glm::vec3 B = glm::vec3(ellipsoid2Sphere*glm::vec4(triangle->vertices[1], 1));
    const glm::vec3 C = glm::vec3(ellipsoid2Sphere*glm::vec4(triangle->vertices[2], 1));

    const glm::vec3 AB = B - A;
    const glm::vec3 BC = C - B;
    const glm::vec3 CA = A - C;
    const glm::vec3 N = glm::normalize(glm::cross(AB, -CA));

    const glm::vec3 start = glm::vec3(0.f, 0.f, 0.f);
    const glm::vec3 end = glm::vec3(ellipsoid2Sphere*glm::vec4(ellipsoidEnd, 1.f));
    const glm::vec3 rayDir = end;

    CollisionData res;
    res.t = INFINITY;
    res.pos = glm::vec3(0.f, 0.f, 0.f);
    res.normal = n;

    const float tOnPlane = CollisionUtils::rayIntersectPlane(start - N, rayDir, A, N);
    if (tOnPlane < 1.f && tOnPlane > 0.f) { // inside the plane

        const glm::vec3 P = tOnPlane*rayDir;
        const glm::vec3 AP = P - A;
        const glm::vec3 BP = P - B;
        const glm::vec3 CP = P - C;

        // AB cross AP, BC cross CP, ...
        if (glm::dot(glm::cross(AB, AP), N) > 0.f &&
                glm::dot(glm::cross(BC, BP), N) > 0.f &&
                glm::dot(glm::cross(CA, CP), N) > 0.f) {
            res.t = tOnPlane; // use closest point
            res.pos = res.t*rayDir;
            res.pos = glm::vec3(sphere2Ellipsoid*glm::vec4(res.pos, 1)); // back to ellipsoid space
            return res;
        } else {
            const float tOnEdge1 = CollisionUtils::rayIntersectEdge(start, end, B, A);
            const float tOnEdge2 = CollisionUtils::rayIntersectEdge(start, end, B, C);
            const float tOnEdge3 = CollisionUtils::rayIntersectEdge(start, end, A, C);
            const float tOnV1 = CollisionUtils::rayIntersectVertex(start, end, A);
            const float tOnV2 = CollisionUtils::rayIntersectVertex(start, end, B);
            const float tOnV3 = CollisionUtils::rayIntersectVertex(start, end, C);

            const float t = std::min(tOnV3, std::min(tOnV2, std::min(tOnV1, std::min(tOnEdge3, std::min(tOnEdge2, tOnEdge1)))));

            if (t < 1.f && t > 0.f) {
                res.t = t;
                res.pos = res.t*rayDir;
                res.pos = glm::vec3(sphere2Ellipsoid*glm::vec4(res.pos, 1.f)); // back to ellipsoid space
                return res;
            }
        }
        } else {
            // check AB, BC, CA edges
            const float tOnEdge1 = CollisionUtils::rayIntersectEdge(start, end, B, A);
            const float tOnEdge2 = CollisionUtils::rayIntersectEdge(start, end, B, C);
            const float tOnEdge3 = CollisionUtils::rayIntersectEdge(start, end, A, C);
            const float tOnV1 = CollisionUtils::rayIntersectVertex(start, end, A);
            const float tOnV2 = CollisionUtils::rayIntersectVertex(start, end, B);
            const float tOnV3 = CollisionUtils::rayIntersectVertex(start, end, C);

            const float t = std::min(tOnV3, std::min(tOnV2, std::min(tOnV1, std::min(tOnEdge3, std::min(tOnEdge2, tOnEdge1)))));

            if (t < 1.f && t > 0.f) {
                res.t = t;
                res.pos = res.t*rayDir;
                res.pos = glm::vec3(sphere2Ellipsoid*glm::vec4(res.pos, 1.f)); // back to ellipsoid space
                return res;
            }
        }
    return res;
}

glm::vec3 EnvironmentCollisionComponent::doNudge(const glm::vec3& initPos,
                                                 CollisionData data,
                                                 const QList<OBJ::Triangle*>& triangles) const {
    glm::vec3 currPos = initPos;
    glm::vec3 nudge = data.normal;
    glm::vec3 posNudge = data.pos + nudge*0.01f;
    for (int i = 0; i < 5; ++i) {
        CollisionData nudgeCollision = getClosestCollision(currPos, posNudge, triangles);
        if (nudgeCollision.t == INF) {
            currPos = posNudge;
            break;
        } else {
            if (glm::length(nudgeCollision.normal - nudge) < EPS || glm::length(nudgeCollision.normal + nudge) < EPS) {
                nudge = -nudgeCollision.normal;
            } else {
                nudge = nudgeCollision.normal;
            }
            posNudge = nudgeCollision.pos + nudge*0.01f;
        }
    }
    return currPos;
}

CollisionData EnvironmentCollisionComponent::getClosestCollision(const glm::vec3& initialPos,
                                                                 const glm::vec3& nextPos,
                                                                 const QList<OBJ::Triangle*>& triangles) const {

    CollisionData closest;
    closest.t = INF;
    for (int i = 0, sz = triangles.size(); i < sz; ++i) {

        const CollisionData result = ellipsoidIntersectTriangle(initialPos, nextPos, triangles[i]);

        if (result.t < closest.t) {
            closest = result;
        }
    }
    return closest;
}

std::pair<std::vector<CollisionData>, glm::vec3> EnvironmentCollisionComponent::ellipsoidTriangleCollisions(const glm::vec3& start,
                                                                                                            const glm::vec3& end,
                                                                                                            const QList<OBJ::Triangle*>& triangles) const {

    std::vector<CollisionData> collisions = {};
    glm::vec3 currPos = start;
    glm::vec3 nextPos = end;

    for (int i = 0; i < 10; ++i) {
        CollisionData c = getClosestCollision(currPos, nextPos, triangles);

        if (c.t == INF) {
            return std::pair<std::vector<CollisionData>, glm::vec3>(collisions, nextPos);

        } else {
            currPos = doNudge(currPos, c, triangles);
            const glm::vec3 d = end - currPos;
            const CollisionData closestCollision = (collisions.empty())? c: collisions.front();
            glm::vec3 dCorrected;
            if (glm::dot(c.normal, glm::vec3(0.f, -1.f, 0.f)) > 0.f) { // downward facing
                dCorrected = d + glm::dot(d, c.normal)*closestCollision.normal;
            } else {
                dCorrected = d - glm::dot(d, c.normal)*closestCollision.normal;
            }

            nextPos = currPos + dCorrected;
            collisions.push_back(c);
        }
    }
    return std::pair<std::vector<CollisionData>, glm::vec3>(collisions, currPos);
}

std::shared_ptr<CollisionEllipsoid> EnvironmentCollisionComponent::getEllipsoid() const  {
    return m_ellipsoid;
}





