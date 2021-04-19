#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H


#include "Component.h"



class PlayerControlComponent: public Component
{
public:
    PlayerControlComponent(GameObject* object,
                           QMap<int, bool> keysPressed,
                           QMap<int, bool> mouseButtonsPressed,
                           glm::vec2 mousePosition);

    virtual void onTick(float seconds) override;

    virtual void onKeyPress(QKeyEvent *event) override;
    virtual void onKeyRepeat(QKeyEvent *event) override;
    virtual void onKeyRelease(QKeyEvent *event) override;

    virtual void onMousePress(QMouseEvent *event, int dx, int dy) override;
    virtual void onMouseMove(int dx, int dy) override;
    virtual void onMouseRelease(QMouseEvent* event, int dx, int dy) override;
    virtual void onMouseWheel(int dx, int dy) override;

    std::shared_ptr<Input> getInput() const;

private:
    std::shared_ptr<Input> m_input;

    bool m_thirdPerson = true;

    float m_velocityY;

    int m_jumpTimer;
};

#endif // PLAYERCONTROLCOMPONENT_H
