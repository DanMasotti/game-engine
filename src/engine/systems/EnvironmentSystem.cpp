#include "EnvironmentSystem.h"
#include "../components/EnvironmentCollisionComponent.h"
#include "../components/TransformComponent.h"
#include "../components/CollisionComponent.h"
#include "../util/SparseSpatialGrid.h"

#include "engine/graphics/Graphics.h"

#include "QSet"

extern bool IS_DEBUG_MODE;

static inline bool isPointInTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& P) {
    float area = 0.5f*glm::l2Norm(glm::cross(B - A, C - A));
    float alpha = glm::l2Norm(glm::cross(B - P, C - P))/(2*area);
    float beta = 0.5f*glm::l2Norm(glm::cross(C - P, A - P))/(2*area);
    float gamma = 1.f - alpha - beta;

    return (alpha > 0.f && alpha < 1.f) &&
            (beta > 0.f && beta < 1.f) &&
            (gamma > 0.f && gamma < 1.f);
}


EnvironmentSystem::EnvironmentSystem(QString worldMesh, QString navMesh):
    System(),
    m_environment(std::make_shared<OBJ>(worldMesh)),
    m_navMesh(std::make_shared<OBJ>(navMesh))
{

    m_grid = std::make_shared<SparseSpatialGrid<OBJ::Triangle*>>(25); // x meters = 1 cell

    for (const auto& triangle: m_environment->triangles) {
        glm::vec3 center = glm::vec3(0.f,0.f,0.f);
        for (const auto& vert: triangle->vertices) {
            center += vert;
            m_grid->put(triangle, vert);
        }
        m_grid->put(triangle, center);
    }
}

void EnvironmentSystem::onTick(float seconds) {
    detect();
}


void EnvironmentSystem::detect() {

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        std::shared_ptr<TransformComponent> transform = it.value()->getComponent<TransformComponent>();
        const glm::vec3 end = transform->getTargetPosition();
        const glm::vec3 start = transform->getPosition();

        std::shared_ptr<EnvironmentCollisionComponent> ellipsoid = it.value()->getComponent<EnvironmentCollisionComponent>();

        const glm::vec3 ellipsoidEye = glm::vec3(0.f, ellipsoid->getEllipsoid()->radius.y, 0.f); // Transform component is point on the floor

        QSet<OBJ::Triangle*> relevantTriangles = {};

        std::unordered_set<OBJ::Triangle*> currCell = m_grid->get(start);
        for (auto const& tri: currCell) {
            relevantTriangles.insert(tri);
        }

        std::unordered_set<OBJ::Triangle*> targetCell = m_grid->get(end);
        for (auto const& tri: targetCell) {
            relevantTriangles.insert(tri);
        }

        const std::pair<std::vector<CollisionData>, glm::vec3> res = ellipsoid->
                ellipsoidTriangleCollisions(start + ellipsoidEye, end + ellipsoidEye, relevantTriangles.values());

        const std::vector<CollisionData> collisions = res.first;
        glm::vec3 currPos = res.second - ellipsoidEye;

        transform->setIsOnGround(false);
        for (int i = 0; i < int(collisions.size()); ++i) {
            if (glm::dot(glm::vec3(0.f, 1.f, 0.f), collisions[i].normal) > 0.f) {
                transform->setIsOnGround(true);
            }
        }

        if (!transform->isMovingLaterally() && transform->isOnGround()) {
            currPos = start;
        }

        transform->setPosition(currPos);
    }
}
