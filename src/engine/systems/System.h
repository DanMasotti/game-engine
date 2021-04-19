#ifndef SYSTEM_H
#define SYSTEM_H

#include "QMap"
#include "QKeyEvent"
#include "engine/util/CommonIncludes.h"

class GameObject;

class System {

public:
    System();
    virtual ~System() {};

    void onKeyPress(QKeyEvent *event);
    void onKeyRepeat(QKeyEvent *event);
    void onKeyRelease(QKeyEvent *event);

    void onMousePress(QMouseEvent *event, int dx, int dy);
    void onMouseMove(int dx, int dy);
    void onMouseRelease(QMouseEvent* event, int dx, int dy);
    void onMouseWheel(int dx, int dy);

    void addGameObject(QString objectID, std::shared_ptr<GameObject> object);
    void removeGameObject(QString objectID);
    std::shared_ptr<GameObject> getGameObject(QString objectID) const;

    bool contains(QString gameObjectId) const;

    virtual void onTick(float seconds);

protected:
    QMap<QString, std::shared_ptr<GameObject>> m_gameObjects;
    int m_gameState;

};


#endif // SYSTEM_H
