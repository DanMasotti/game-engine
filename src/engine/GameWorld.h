#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "QMap"
#include "QList"
#include "QQueue"
#include "QKeyEvent"
#include "engine/util/TypeMap.h"

class Graphics;
class GameObject;
class System;
class Screen;

class GameWorld
{
public:
    GameWorld(Screen* screen, QString worldMesh = "NONE", QString navMesh = "NONE");
    ~GameWorld();

    void onMousePress(QMouseEvent *event, int dx, int dy);
    void onMouseMove(int dx, int dy);
    void onMouseRelease(QMouseEvent* event, int dx, int dy);
    void onMouseWheel(int dx, int dy);

    void onKeyPress(QKeyEvent *event);
    void onKeyRepeat(QKeyEvent *event);
    void onKeyRelease(QKeyEvent *event);

    /*
     * Components
     */
    void addGameObject(QString gameObjectID, std::shared_ptr<GameObject> gameObject);
    void removeGameObject(QString gameObjectID);
    std::shared_ptr<GameObject> getGameObject(QString gameObjectID) const ;
    QMap<QString, std::shared_ptr<GameObject>> getGameObjects() const;

    /*
     *  Systems
     */
    template<typename Sys>
    void addSystem(std::shared_ptr<Sys> &&s) {
        m_systems.put<Sys>(s);
    };

    template<typename Sys>
    void removeSystem() {
        m_systems.remove<Sys>();
    };

    template<typename  Sys>
    std::shared_ptr<Sys> getSystem() const {
        auto it = m_systems.find<Sys>();
        assert(it != m_systems.end());
        return std::static_pointer_cast<Sys>(it->second);
    };

    void tick(float seconds);

    void draw(Graphics* g);

    void flagObject(QString objectID);

    void setGameState(int gameState);

private:
    QString m_worldMesh;
    QString m_navMesh;

    QMap<QString, std::shared_ptr<GameObject>> m_gameObjects;

    QVector<QString> m_flaggedObjects;

    TypeMap<std::shared_ptr<System>> m_systems;

    int m_gameState;

    Screen* m_screen;
};

#endif // GAMEWORLD_H
