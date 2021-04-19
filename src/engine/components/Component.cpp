#include "Component.h"
#include "../GameObject.h"

Component::Component(GameObject* object):
    m_gameObject(object)
{
}


void Component::onKeyPress(QKeyEvent *event) {

}

void Component::onKeyRepeat(QKeyEvent *event) {

}

void Component::onKeyRelease(QKeyEvent *event) {

}

void Component::onMousePress(QMouseEvent *event, int dx, int dy) {

}

void Component::onMouseMove(int dx, int dy) {

}

void Component::onMouseRelease(QMouseEvent* event, int dx, int dy) {

}

void Component::onMouseWheel(int dx, int dy) {

}

void Component::onTick(float seconds) {

}

GameObject* Component::getGameObject() const {
    return m_gameObject;
}

