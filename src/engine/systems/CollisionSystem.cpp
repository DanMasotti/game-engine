#include "CollisionSystem.h"
#include "../components/CollisionComponent.h"
#include "../components/CollisionResponseComponent.h"
#include "../components/TransformComponent.h"


CollisionSystem::CollisionSystem():
    System()
{
    m_cell2Objects = std::unordered_map<int, std::unordered_set<std::shared_ptr<GameObject>>>();
    m_object2Cell = std::unordered_map<std::shared_ptr<GameObject>, int>(m_gameObjects.size());
    m_meters2Cell = 5;

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        std::shared_ptr<TransformComponent> transform = it.value()->getComponent<TransformComponent>();
        const glm::vec3 p = transform->getPosition();
        const int cell = point2Cell(p);
        if (m_cell2Objects[cell].empty()) {
            m_cell2Objects[cell] = {it.value()};
        } else {
            m_cell2Objects[cell].insert(it.value());
        }
        m_object2Cell[it.value()] = cell;
    }
}

// make all OBJs live on the GPU and then tell draw what to use every tick
void CollisionSystem::onTick(float seconds) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        std::shared_ptr<TransformComponent> transform = it.value()->getComponent<TransformComponent>();
        const glm::vec3 p = transform->getPosition();
        const int currCell = point2Cell(p);
        const int oldCell = m_object2Cell[it.value()];

        m_object2Cell[it.value()] = currCell;

        // take out object from it's old place
        if (m_cell2Objects.find(oldCell) != m_cell2Objects.end()) {
            m_cell2Objects[oldCell].erase(it.value());
        }

        // put it into its new cell
        if (m_cell2Objects[currCell].empty()) {
            m_cell2Objects[currCell] = {it.value()};
        } else {
            m_cell2Objects[currCell].insert(it.value());
        }
    }

    detect();
}

int CollisionSystem::point2Cell(const glm::vec3 &p) {
    const int X = static_cast<int>((p.x > 0.f)? floor(p.x/m_meters2Cell): ceil(p.x/m_meters2Cell));
    const int Y = static_cast<int>((p.y > 0.f)? floor(p.y/m_meters2Cell): ceil(p.y/m_meters2Cell));
    const int Z = static_cast<int>((p.z > 0.f)? floor(p.z/m_meters2Cell): ceil(p.z/m_meters2Cell));

    std::size_t seed = 3;
    seed ^= X + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= Y + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= Z + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
}

void CollisionSystem::detect() {
    for (auto i = m_gameObjects.begin(); i != m_gameObjects.end(); i++) {
        const int cell = m_object2Cell[i.value()];
        std::unordered_set<std::shared_ptr<GameObject>> cellmates = m_cell2Objects[cell];

        for (auto const& j: cellmates) {
            if (i.key() == j->getID()) {
                continue;
            }

            std::shared_ptr<CollisionComponent> comp1 = i.value()->getComponent<CollisionComponent>();
            std::shared_ptr<CollisionComponent> comp2 = j->getComponent<CollisionComponent>();
            comp1->collide(comp2.get());
        }
    }
};



