#ifndef GRAPH_H
#define GRAPH_H

#include "unordered_map"
#include "unordered_set"
#include "list"
#include "set"
#include "glm/glm.hpp"
#include "../util/CommonIncludes.h"

// GOAP semantic but not clear how to complete that
// State Machines?  Planning plugins for unreal
// https://www.unrealengine.com/marketplace/en-US/product/goap-npc-goal-oriented-action-planning-for-non-player-characters
// change heuristic of A star to be in front of the behavior | tweaking so that an enemy is on a node it becomes invalid |
// AI jump from one platform to another platform | really good navmesh navigation

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};


template <class T>
struct Node {
    T data;
    glm::vec3 pos;
    float f;
    float g;
    float h;
    std::shared_ptr<Node> prev;
};


// T should be a pointer
template <class T>
class Graph {
     // node to its neighbors

public:
    Graph();
    ~Graph();

    void addEdge(std::shared_ptr<Node<T>> node1, std::shared_ptr<Node<T>> node2, float weight = 1.f);

    std::list<std::shared_ptr<Node<T>>> neighborsOf(std::shared_ptr<Node<T>> node);

    std::unordered_set<std::shared_ptr<Node<T>>> getNodes();

    std::pair<bool, std::shared_ptr<Node<T>>> AStar(std::shared_ptr<Node<T>> start, std::shared_ptr<Node<T>> goal);

private:
    std::unordered_map<std::shared_ptr<Node<T>>, std::list<std::shared_ptr<Node<T>>>> m_map;
    std::unordered_set<std::shared_ptr<Node<T>>> m_nodes;
    std::unordered_map<std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>>, float, hash_pair> m_edgeWeights;
};

template <class T>
Graph<T>::Graph() {}

template <class T>
Graph<T>::~Graph(){}

template<class T>
void Graph<T>::addEdge(std::shared_ptr<Node<T>> node1, std::shared_ptr<Node<T>> node2, float weight) {
    if (m_map.find(node1) == m_map.end()) {
        m_map[node1] = {node2};
        m_map[node2] = {node1};
    } else {
        m_map[node1].push_back(node2);
        m_map[node2].push_back(node1);
    }

    m_nodes.insert(node1);
    m_nodes.insert(node2);

    const auto key1 = std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>>(node1, node2);
    const auto key2 = std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>>(node2, node1);
    m_edgeWeights[key1] = weight; // TODO: mud/terrain should be weighted more than distance
    m_edgeWeights[key2] = weight;
}

template <class T>
std::list<std::shared_ptr<Node<T>>> Graph<T>::neighborsOf(std::shared_ptr<Node<T>> node){
    if (m_map.find(node) != m_map.end()) {
        return m_map[node];
    } else {
        return {};
    }
}

template <class T>
std::pair<bool, std::shared_ptr<Node<T>>> Graph<T>::AStar(std::shared_ptr<Node<T>> start, std::shared_ptr<Node<T>> goal) {
    // reset everything
    for (auto& it : m_nodes) {
        it->h = glm::distance(it->pos, goal->pos);
        it->g = INFINITY;
        it->f = INFINITY;
        it->prev = nullptr;
    }

    auto nodeComp = [](std::shared_ptr<Node<T>> lhs, std::shared_ptr<Node<T>> rhs) {
            return lhs->f < rhs->f;
        };
    std::set<std::shared_ptr<Node<T>>, decltype (nodeComp)> openSet(nodeComp);

    start->h = 0.f;
    start->g = 0.f;
    start->f = start->h;

    openSet.insert(start);

    while (!openSet.empty()) {

        auto iter = openSet.begin();
        std::shared_ptr<Node<T>> current = *iter;

        if (current == goal) {
           return std::pair<bool, std::shared_ptr<Node<T>>>(true, current);
        }

        openSet.erase(iter);

        std::list<std::shared_ptr<Node<T>>> neighbors = neighborsOf(current);
        for (auto& neighbor: neighbors) {

            const auto key = std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>>(current, neighbor);
            const float weight = m_edgeWeights[key];
            float g = current->g + weight*glm::distance(current->pos, neighbor->pos);

            if (g < neighbor->g) {
                neighbor->prev = current;
                neighbor->g = g;
                neighbor->f = neighbor->g + neighbor->h;

                if (openSet.find(neighbor) == openSet.end()) {
                    openSet.insert(neighbor);
                }
            }
        }
    }
    // there is no path
    return std::pair<bool, std::shared_ptr<Node<T>>>(false, nullptr);
}

template <class T>
std::unordered_set<std::shared_ptr<Node<T>>> Graph<T>::getNodes() {
    return m_nodes;
}


#endif // GRAPH_H
