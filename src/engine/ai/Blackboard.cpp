#include "Blackboard.h"
#include "../GameWorld.h"
#include "../components/TransformComponent.h"
#include "../GameObject.h"

#include "engine/util/RNG.h"


// blackboard get/set from each of the components just a map
// https://www.youtube.com/watch?v=iY1jnFvHgbE&t=843s
static inline bool isPointInTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& P) {
    float area = 0.5f*glm::l2Norm(glm::cross(B - A, C - A));
    float alpha = glm::l2Norm(glm::cross(B - P, C - P))/(2*area);
    float beta = 0.5f*glm::l2Norm(glm::cross(C - P, A - P))/(2*area);
    float gamma = 1.f - alpha - beta;

    return (alpha > 0.f && alpha < 1.f) &&
            (beta > 0.f && beta < 1.f) &&
            (gamma > 0.f && gamma < 1.f);
}

// Navmesh in the environment and creates the graph and someone else asks for it
Blackboard::Blackboard(QString filepath, GameWorld* world):
    m_world(world),
    m_navMesh(std::make_shared<OBJ>(filepath))
{
    m_edges2Vindices = {};
    m_graph = std::make_shared<Graph<OBJ::Triangle*>>();

    std::unordered_map<std::shared_ptr<Node<OBJ::Triangle*>>, std::set<int>> node2Vindices = {};

    for (auto it = m_navMesh->triangles.begin(); it != m_navMesh->triangles.end(); ++it) {
        glm::vec3 center = glm::vec3(0.f,0.f,0.f);
        auto triangle = *it;

        for (const auto& vert: triangle->vertices) {
            center += vert;
        }

        std::shared_ptr<Node<OBJ::Triangle*>> node = std::make_shared<Node<OBJ::Triangle*>>();
        node->pos = center;
        node->data = triangle;

        node2Vindices[node] = std::set<int>({triangle->a.vertexIndex, triangle->b.vertexIndex, triangle->c.vertexIndex});
    }

    for (auto i = node2Vindices.begin(); i != node2Vindices.end(); ++i) {
        std::set<int> vindices1 = node2Vindices[i->first];

        for (auto j = node2Vindices.begin(); j != node2Vindices.end(); ++j) {

            if (i->first == j->first) {
                continue;
            }

            std::set<int> vindices2 = node2Vindices[j->first];

            std::vector<int> intersection;

            std::set_intersection(vindices1.begin(), vindices1.end(),
                                  vindices2.begin(), vindices2.end(),
                                  std::back_inserter(intersection));

            if (intersection.size() == 2) {
                m_graph->addEdge(i->first, j->first);
                m_edges2Vindices[std::pair<std::shared_ptr<Node<OBJ::Triangle*>>, std::shared_ptr<Node<OBJ::Triangle*>>>(i->first, j->first)] = intersection;
                m_edges2Vindices[std::pair<std::shared_ptr<Node<OBJ::Triangle*>>, std::shared_ptr<Node<OBJ::Triangle*>>>(j->first, i->first)] = intersection;
            }
        }
    }
}

std::vector<glm::vec3> Blackboard::getPath(std::shared_ptr<Node<OBJ::Triangle*>> currentNode,
                                         std::shared_ptr<Node<OBJ::Triangle*>> targetNode,
                                         const glm::vec3& target) {

    std::pair<bool, std::shared_ptr<Node<OBJ::Triangle*>>> res = m_graph->AStar(currentNode, targetNode);

    if (res.first) {
         std::shared_ptr<Node<OBJ::Triangle*>> current = res.second; // K
         std::vector<glm::vec3> positions = {target};

         std::vector<std::pair<glm::vec3, glm::vec3>> portals = {};

         while (current->prev) {
             std::vector<int> vindices = m_edges2Vindices[std::pair<std::shared_ptr<Node<OBJ::Triangle*>>,
                     std::shared_ptr<Node<OBJ::Triangle*>>>(current, current->prev)]; // edge shared by K & G | G & C | C & A

             const glm::vec3 v1 = m_navMesh->vertices[vindices[0]];
             const glm::vec3 v2 = m_navMesh->vertices[vindices[1]];
             const glm::vec3 midpt = 0.5f*v1 + 0.5f*v2;

             const glm::vec3 A = current->data->vertices[0];
             const glm::vec3 B = current->data->vertices[1];
             const glm::vec3 C = current->data->vertices[2];
             const glm::vec3 centroid = 0.333f*(A + B + C);

             const glm::vec3 ray = midpt - centroid;
             const glm::vec3 rayPlusOne = ray + glm::vec3(0.f, 1.f, 0.f);

             const glm::vec3 n = glm::cross(ray, rayPlusOne);

             glm::vec3 left;
             glm::vec3 right;
             if (glm::dot(v1 - midpt, n) > 0.f) {
                 left = v1;
                 right = v2;
             } else {
                 left = v2;
                 right = v1;
             }
             portals.push_back(std::pair<glm::vec3, glm::vec3>(left, right));

             current = current->prev;
         }

         if (!portals.empty()) {
             glm::vec3 apex = target;
             glm::vec3 left = portals[0].first;
             glm::vec3 right = portals[1].second;

             int i = 1;
             while (i < int(portals.size()) - 1 ) {
                 std::pair<glm::vec3, glm::vec3> portal = portals[i];
                 glm::vec3 leftVert = portal.first;
                 glm::vec3 rightVert = portal.second;

                 bool isPointInFunnel = isPointInTriangle(apex, left, right, leftVert);

                 if (isPointInFunnel) {
                     left = leftVert;
                 } else {
                     positions.push_back(right);
                     apex = right;
                     i++;
                     continue;
                 }

                 isPointInFunnel = isPointInTriangle(apex, left, right, rightVert);
                 if (isPointInFunnel) {
                     right = rightVert;
                 } else {
                     positions.push_back(left);
                     apex = left;
                     i++;
                     continue;
                 }
             }
         }
         return positions;
    }
    return {};
}

std::shared_ptr<Node<OBJ::Triangle*>> Blackboard::point2Node(const glm::vec3 &p) {
    std::shared_ptr<Node<OBJ::Triangle*>> node = *m_graph->getNodes().begin();
    float dist = 100000.f;
    for (const auto& tri: m_graph->getNodes()) {
        const glm::vec3 A = tri->data->vertices[0];
        const glm::vec3 B = tri->data->vertices[1];
        const glm::vec3 C = tri->data->vertices[2];
        const glm::vec3 centroid = 0.333f*(A + B + C);
        if (glm::distance(centroid, p) < dist) {
            node = tri;
            dist = glm::distance(centroid, p);
        }
    }
    return node;
}

glm::vec3 Blackboard::getPositionOf(QString name) {
    if (m_gameObject2Location.find(name) != m_gameObject2Location.end()) {
        const glm::vec3 pos = m_world->getGameObject(name)->getComponent<TransformComponent>()->getPosition();
        m_gameObject2Location[name] = pos;
    } else if (name == "random") {
        const RNG rng = RNG();
        return glm::vec3(rng.getRandomNumber() * 10., rng.getRandomNumber() * 10., rng.getRandomNumber() * 10.);
    }
    return m_gameObject2Location[name];
}

std::pair<float, glm::vec3> Blackboard::getRotationOf(QString name) {
    if (m_gameObject2Location.find(name) != m_gameObject2Location.end()) {
        std::pair<float, glm::vec3> res = m_world->getGameObject(name)->getComponent<TransformComponent>()->getRotation();
        return res;
    }
    return std::pair<float, glm::vec3>(0.f, glm::vec3(0, 0, 0));
}

void Blackboard::update() {
    for (auto it = m_gameObject2Location.begin(); it != m_gameObject2Location.end(); ++it) {
        const QString key = it.key();
        const glm::vec3 pos = m_world->getGameObject(key)->getComponent<TransformComponent>()->getPosition();
        m_gameObject2Location[key] = pos;
    }
}


