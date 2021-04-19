#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include "glm/glm.hpp"
#include "QString"
#include "../graphics/obj.h"
#include "../ai/Graph.h"
#include "QMap"

class GameWorld;

class Blackboard
{
public:
    Blackboard(QString filepath, GameWorld* world);

    glm::vec3 getPositionOf(QString name);
    std::pair<float, glm::vec3> getRotationOf(QString name);

    std::vector<glm::vec3> getPath(std::shared_ptr<Node<OBJ::Triangle*>> start,
                                   std::shared_ptr<Node<OBJ::Triangle*>> target,
                                   const glm::vec3& targetPos);

    std::shared_ptr<Node<OBJ::Triangle*>> point2Node(const glm::vec3& p);

    void update();

private:
    GameWorld* m_world;
    std::shared_ptr<OBJ> m_navMesh;
    std::shared_ptr<Graph<OBJ::Triangle*>> m_graph;
    std::unordered_map<std::pair<std::shared_ptr<Node<OBJ::Triangle*>>, std::shared_ptr<Node<OBJ::Triangle*>>>,
        std::vector<int>, hash_pair> m_edges2Vindices;

    QMap<QString, glm::vec3> m_gameObject2Location;

};

#endif // BLACKBOARD_H
