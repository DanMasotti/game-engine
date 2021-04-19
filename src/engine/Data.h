#ifndef STRUCTS_H
#define STRUCTS_H

#include "util/CommonIncludes.h"
#include "QKeyEvent"

// Could imagine a fighting game with combos of keys for example
struct Input {
    QMap<int, bool> keysPressed;
    QMap<int, bool> mouseKeysPressed;
    glm::vec2 mousePosition;

    Input(QMap<int, bool> keysPressed, QMap<int, bool> mouseKeysPressed, glm::vec2 mousePosition):
        keysPressed(keysPressed),
        mouseKeysPressed(mouseKeysPressed),
        mousePosition(mousePosition){}
};

struct Transform {
    glm::vec3 scale;

    float angle;
    glm::vec3 axis;

    glm::vec3 translate;

    Transform(glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 translate):
        scale(scale), angle(angle), axis(axis), translate(translate) {}
};

// dynamic collisions
struct CollisionCylinder {
    glm::vec3 position;
    float radius;
    float height;

    CollisionCylinder(glm::vec3 position, float radius, float height):
        position(position), radius(radius), height(height) {}
};

// static collisions
struct CollisionEllipsoid {
    glm::vec3 radius;

    CollisionEllipsoid(glm::vec3 radius):
        radius(radius) {}
};

struct CollisionData {
    float t;
    glm::vec3 normal;
    glm::vec3 pos;
};

#endif // STRUCTS_H
