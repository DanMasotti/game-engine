#include "PlayerControlComponent.h"
#include "../graphics/Graphics.h"
#include "../graphics/Camera.h"

#include "../components/TransformComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/EnvironmentCollisionComponent.h"
#include "../components/CollisionComponent.h"


extern bool IS_DEBUG_MODE;

PlayerControlComponent::PlayerControlComponent(GameObject* object,
                                               QMap<int, bool> keysPressed,
                                               QMap<int, bool> mouseButtonsPressed,
                                               glm::vec2 mousePosition):
    Component(object),
    m_input(std::make_shared<Input>(keysPressed, mouseButtonsPressed, mousePosition)),
    m_velocityY(0.f),
    m_jumpTimer(-1)
{

}

void PlayerControlComponent::onKeyPress(QKeyEvent *event) {
    m_input->keysPressed[event->key()] = true;
}

void PlayerControlComponent::onKeyRepeat(QKeyEvent *event) {
    m_input->keysPressed[event->key()] = true;
}

void PlayerControlComponent::onKeyRelease(QKeyEvent *event) {
    m_input->keysPressed[event->key()] = false;
}

void PlayerControlComponent::onMousePress(QMouseEvent *event, int dx, int dy) {
    m_input->mouseKeysPressed[event->button()] = true;
}

void PlayerControlComponent::onMouseMove(int dx, int dy) {
    Graphics *g = Graphics::getGlobalInstance();
    std::shared_ptr<Camera> cam = g->getActiveCamera();
    cam->rotate(-float(dx)/10000.f, -float(dy)/10000.f);
}

void PlayerControlComponent::onMouseRelease(QMouseEvent* event, int dx, int dy) {
    m_input->mouseKeysPressed[event->button()] = false;
}

void PlayerControlComponent::onMouseWheel(int dx, int dy) {

}

void PlayerControlComponent::onTick(float seconds) {
    const std::shared_ptr<Camera> camera = Graphics::getGlobalInstance()->getActiveCamera();
    const glm::vec3 look = camera->getLook();
    const glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    const glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    if (IS_DEBUG_MODE) { // for an out of body experience

        if (m_input->keysPressed[Qt::Key_W] || m_input->keysPressed[Qt::Key_Up]) {
            camera->setEye(camera->getEye() + dir);
        }

        if (m_input->keysPressed[Qt::Key_S] || m_input->keysPressed[Qt::Key_Down]) {
            camera->setEye(camera->getEye() - dir);
        }

        if (m_input->keysPressed[Qt::Key_A] || m_input->keysPressed[Qt::Key_Left]) {
            camera->setEye(camera->getEye() + perp);
        }

        if (m_input->keysPressed[Qt::Key_D] || m_input->keysPressed[Qt::Key_Right]) {
            camera->setEye(camera->getEye() - perp);
        }

        if (m_input->keysPressed[Qt::Key_Space]) {
            camera->setEye(camera->getEye() + glm::vec3(0, 1, 0));
        }

        if (m_input->keysPressed[Qt::Key_E] || m_input->keysPressed[Qt::Key_0]) {
            camera->setEye(camera->getEye() - glm::vec3(0, 1, 0));
        }

    } else {
        std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();

        glm::vec3 currPos = transformer->getPosition();

        transformer->setIsMovingLaterally(false);

        std::shared_ptr<AnimationComponent> animator = m_gameObject->getComponent<AnimationComponent>();

        const float speed = 0.1f;

        bool isForward = glm::dot(dir, glm::vec3(0, 0, -1));
        float headingAngle = glm::acos(glm::dot((isForward)? dir: -dir, glm::vec3(0, 0, -1))/(glm::l2Norm(dir))) + M_PI/2.f;

        if (m_input->keysPressed[Qt::Key_F5]) {
            m_thirdPerson = !(m_thirdPerson );
        }

        if (m_input->keysPressed[Qt::Key_W] || m_input->keysPressed[Qt::Key_Up]) {
            transformer->setIsMovingLaterally(true);
            if (transformer->isOnGround()) animator->switchSequence("run");
            currPos += speed*dir;
        }

        if (m_input->keysPressed[Qt::Key_S] || m_input->keysPressed[Qt::Key_Down]) {
            transformer->setIsMovingLaterally(true);
            if (transformer->isOnGround()) animator->switchSequence("run");
            currPos -= speed*dir;
        }

        if (m_input->keysPressed[Qt::Key_A] || m_input->keysPressed[Qt::Key_Left]) {
            transformer->setIsMovingLaterally(true);
            if (transformer->isOnGround()) animator->switchSequence("strafe_left");
            currPos += speed*perp;
        }

        if (m_input->keysPressed[Qt::Key_D] || m_input->keysPressed[Qt::Key_Right]) {
            transformer->setIsMovingLaterally(true);
            if (transformer->isOnGround()) animator->switchSequence("strafe_right");
            currPos -= speed*perp;
        }

        if (m_input->keysPressed[Qt::Key_Space]) {
            if (transformer->isOnGround()) {
               animator->switchSequence("jump", false);
               transformer->setIsOnGround(false);
               m_velocityY = 0.3f;
            }
        }

        currPos.y += m_velocityY;
        if (transformer->isOnGround()) {
            if (m_velocityY < 0.f) {
                m_velocityY = 0.f;
            }
        }

        m_velocityY -= 0.25f*seconds;

        transformer->setTargetPosition(currPos, 1);
        transformer->rotate(headingAngle, glm::vec3(0, 1, 0));

        if (m_input->mouseKeysPressed[Qt::LeftButton]) {
            animator->switchSequence("punch_left", false);
        }

        if (m_input->mouseKeysPressed[Qt::RightButton]) {
            animator->switchSequence("punch_right", false);
        }

        if (m_input->mouseKeysPressed[Qt::MiddleButton]) {
            animator->switchSequence("kick", false);
        }
        const glm::vec3 offset = (m_thirdPerson)? -2.f*look + glm::vec3(0.f, 1.f, 0.f) : glm::vec3(0.f, 1.f, 0.f);
        camera->setEye(transformer->getPosition() + offset);
    }
}

std::shared_ptr<Input> PlayerControlComponent::getInput() const {
    return m_input;
}



