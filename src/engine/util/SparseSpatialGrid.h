#ifndef SPARSESPATIALGRID_H
#define SPARSESPATIALGRID_H

#include "QMap"
#include <unordered_map>
#include <unordered_set>
#include "glm/glm.hpp"


template <class T>
class SparseSpatialGrid
{
public:
    SparseSpatialGrid(float meters2Cell);
    ~SparseSpatialGrid();

    void put(const T& entity, const glm::vec3& p);

    void put(const T& entity, int cell);

    std::unordered_set<T> get(int cell) ;

    std::unordered_set<T> get(const glm::vec3& p) ;

    void move(const T& entity, const glm::vec3& p);

    void whereIs(const T& entity);

    int point2Cell(const glm::vec3& p) const;

    std::unordered_map<int, std::unordered_set<T>> getGrid() const;

private:
    float m_meters2Cell;
    std::unordered_map<T, int> m_entity2Cell;
    std::unordered_map<int, std::unordered_set<T>> m_cell2Entities;
};


template <class T>
SparseSpatialGrid<T>::SparseSpatialGrid(float meters2Cell):
    m_meters2Cell(meters2Cell),
    m_entity2Cell(std::unordered_map<T, int>()),
    m_cell2Entities(std::unordered_map<int, std::unordered_set<T>>())
{ }

template <class T>
SparseSpatialGrid<T>::~SparseSpatialGrid() { };

template <class T>
int SparseSpatialGrid<T>::point2Cell(const glm::vec3& p) const {
    const int X = static_cast<int>((p.x > 0.f)? floor(p.x/m_meters2Cell): ceil(p.x/m_meters2Cell));
    const int Y = static_cast<int>((p.y > 0.f)? floor(p.y/m_meters2Cell): ceil(p.y/m_meters2Cell));
    const int Z = static_cast<int>((p.z > 0.f)? floor(p.z/m_meters2Cell): ceil(p.z/m_meters2Cell));

    std::size_t seed = 3;
    seed ^= X + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= Y + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= Z + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
}

template <class T>
void SparseSpatialGrid<T>::put(const T& entity, const glm::vec3& p) {
    const int cell = point2Cell(p);
    if (m_cell2Entities.find(cell) == m_cell2Entities.end()) {
        m_cell2Entities[cell] = {entity};
    } else {
        m_cell2Entities[cell].insert(entity);
    }
    m_entity2Cell[entity] = cell;
}

template <class T>
void SparseSpatialGrid<T>::put(const T& entity, int cell) {
    if (m_cell2Entities.find(cell) == m_cell2Entities.end()) {
        m_cell2Entities[cell] = {entity};
    } else {
        m_cell2Entities[cell].insert(entity);
    }
    m_entity2Cell[entity] = cell;
}

template <class T>
std::unordered_set<T> SparseSpatialGrid<T>::get(int cell) {
    return m_cell2Entities[cell];
}

template <class T>
std::unordered_set<T> SparseSpatialGrid<T>::get(const glm::vec3& p)  {
    int cell = point2Cell(p);
    return m_cell2Entities[cell];
}

template <class T>
void SparseSpatialGrid<T>::move(const T& entity, const glm::vec3& p) {
    int oldCell = m_entity2Cell[entity];
    int newCell = point2Cell(p);
    if (oldCell != newCell) {
        if (m_cell2Entities.find(oldCell) != m_cell2Entities.end()) {
            std::unordered_set<T> cellmates = m_cell2Entities[oldCell];
            cellmates.erase(entity);
            this->put(entity, p);
        }
    }
}



#endif // SPARSESPATIALGRID_H
