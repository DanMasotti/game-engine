#ifndef COLLISIONUTILS_H
#define COLLISIONUTILS_H

#include "engine/util/CommonIncludes.h"

namespace CollisionUtils {

static inline float sq(float x) {
    return x*x;
}

static inline glm::vec2 getQuadradicRoots(float A, float B, float C) {
    float det = B*B - 4*A*C;
    if (det > 0.f) {
        float t1 = (-B + sqrt(det))/(2.f*A);
        float t2 = (-B - sqrt(det))/(2.f*A);

        if (t1 < 0.f) {
            t1 = INFINITY;
        }
        if (t2 < 0.f) {
            t2 = INFINITY;
        }
        return glm::vec2(t1, t2);
    }
    return glm::vec2(INFINITY, INFINITY);
}

static inline float rayIntersectPlane(const glm::vec3& P, const glm::vec3& d, glm::vec3 S, glm::vec3 normal) {
    float t = INFINITY;
    const float denom = glm::dot(normal, d);
    if (abs(denom) > 0.f) {
        t = glm::dot((S - P), normal)/denom;
    }
    return t;
}

static inline float rayIntersectEdge(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D) {
    const float a = sq(glm::l2Norm(glm::cross(B - A, D - C)));
    const float b = 2.f*(glm::dot(glm::cross(B - A, D - C), glm::cross(A - C, D - C)));
    const float c = sq(glm::l2Norm(glm::cross(A - C, D - C))) - sq(glm::l2Norm(D - C));
    const glm::vec2 tVals = getQuadradicRoots(a, b, c);
    const float minT = (tVals.x < tVals.y)? tVals.x : tVals.y;
    const glm::vec3 P = A + (B - A)*minT;
    const float checkVal = glm::dot(P - C, D - C);
    const bool isWithin = checkVal > 0.f && checkVal < sq(glm::l2Norm(D - C));

    return (isWithin)? minT: INFINITY;
}

static inline float rayIntersectSphere(const glm::vec3 o, const glm::vec3 d) {
    const float a = sq(d.x) + sq(d.y) + sq(d.z);
    const float b = 2.f*(o.x*d.x + o.y*d.y + o.z*d.z);
    const float c = sq(o.x) + sq(o.y) + sq(o.z) - 1.f;
    const glm::vec2 tVals = getQuadradicRoots(a, b, c);
    const float minT = (tVals.x < tVals.y)? tVals.x : tVals.y;
    return minT;
}

static inline float rayIntersectVertex(const glm::vec3& A, const glm::vec3& B, const glm::vec3& V) {
    const glm::vec3 oppositeDir = A - B;
    return rayIntersectSphere(V, oppositeDir);
}

static inline float rayIntersectTriangle(const glm::vec3& start, const glm::vec3& end, const glm::vec3& A, const glm::vec3& B, const glm::vec3& C) {
    glm::vec3 edge1, edge2, h, s, q, rayDir;
    rayDir = end - start;
    float a, f, u, v;
    edge1 = B - A;
    edge2 = C - A;

    h = glm::cross(rayDir, edge2);
    a = glm::dot(edge1,h);
    if (a > -0.00001f && a  < 0.00001f) {
      return INFINITY;
    }
    f = 1.f/a;
    s = start - A;
    u = f * glm::dot(s, h);
    if (u < 0.f || u > 1.f) {
        return INFINITY;
    }
    q = glm::cross(s, edge1);
    v = f * glm::dot(rayDir, q);
    if (v < 0.f || u + v > 1.f) {
        return INFINITY;
    }
    float t = f * glm::dot(edge2, q);
    if (t > 0.00001f) {
        return t;
    } else {
       return INFINITY;
    }
}


}


#endif // COLLISIONUTILS_H
