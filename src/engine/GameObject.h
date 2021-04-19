#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "util/TypeMap.h"
#include "QKeyEvent"
#include "QString"

#include "glm/glm.hpp"
#include "GameWorld.h"

class Component;

class System;

enum SYSTEM_TYPE {
    COLLISION,
    DRAW,
    TICK,
    ANIMATION,
    ENVIRONMENT,
    AI,
    UI,
    PHYSICS
};

class GameObject
{
public:
    GameObject(GameWorld* world, QString id, glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 translate);
    virtual ~GameObject() {};

    void onMousePress(QMouseEvent *event, int dx, int dy);
    void onMouseMove(int dx, int dy);
    void onMouseRelease(QMouseEvent *event, int dx, int dy);
    void onMouseWheel(int dx, int dy);

    void onKeyPress(QKeyEvent *event);
    void onKeyRepeat(QKeyEvent *event);
    void onKeyRelease(QKeyEvent *event);

    template<typename Comp>
    void addComponent(std::shared_ptr<Comp> &&c) {
        m_components.put<Comp>(c);
    };

    template<typename Comp>
    void removeComponent() {
        m_components.remove<Comp>();
    };

    template<typename  Comp>
    std::shared_ptr<Comp> getComponent() const {
        auto it = m_components.find<Comp>();
        assert(it != m_components.end());
        return std::static_pointer_cast<Comp>(it->second);
    };

    template<typename  Sys>
    std::shared_ptr<Sys> getSystem() const {
        return std::static_pointer_cast<Sys>(m_world->getSystem<Sys>());
    };

    std::vector<SYSTEM_TYPE> getSystemFlags() const;

    QString getID() const;

    void messageSystem(SYSTEM_TYPE systemFlag, const glm::vec3& data);

    void tick(float seconds);

    int getTime() const;

    GameWorld* getWorld() const;

    void incrementTimer();

    void setGameState(int gameState);

    void deleteSelf();

    void addSystemFlag(SYSTEM_TYPE type);

protected:

    TypeMap<std::shared_ptr<Component>> m_components;
    GameWorld* m_world;
    QString m_id;
    int m_gameState;
    std::vector<SYSTEM_TYPE> m_systemFlags;

    int m_timer;
};

#endif // GAMEOBJECT_H
