#ifndef COMPONENT_H
#define COMPONENT_H

#include "../GameObject.h" // avoid Circular dependency
#include "../Data.h"
#include "QKeyEvent"



class Component {

public:
    Component(GameObject* object);
    virtual ~Component(){};

    virtual void onKeyPress(QKeyEvent *event);
    virtual void onKeyRepeat(QKeyEvent *event);
    virtual void onKeyRelease(QKeyEvent *event);

    virtual void onMousePress(QMouseEvent *event, int dx, int dy);
    virtual void onMouseMove(int dx, int dy);
    virtual void onMouseRelease(QMouseEvent *event, int dx, int dy);
    virtual void onMouseWheel(int dx, int dy);

    virtual void onTick(float seconds);
    void setGameState(int gameState);

    GameObject* getGameObject() const;

protected:
    GameObject* m_gameObject; //So we can talk back to the game object
    int m_gameState;
};


#endif // COMPONENT_H
