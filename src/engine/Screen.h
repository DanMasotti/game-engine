#ifndef SCREEN_H
#define SCREEN_H

#include "engine/util/CommonIncludes.h"
#include "QKeyEvent"

class Graphics;
class Camera;
class Application;
class GameWorld;

class Screen
{
public:
    Screen(Application* app, std::shared_ptr<Camera> cam);
    virtual ~Screen() {};

    void onMousePress(QMouseEvent *event, int dx, int dy);
    void onMouseMove(int dx, int dy);
    void onMouseRelease(QMouseEvent* event, int dx, int dy);
    void onMouseWheel(int dx, int dy);

    void onKeyPress(QKeyEvent *event);
    void onKeyRepeat(QKeyEvent *event);
    void onKeyRelease(QKeyEvent *event);

    void tick(const float seconds);
    void draw(Graphics* g);
    void resize(const int width, const int height);

    void setGameState(int gameState);

    std::shared_ptr<Camera> getCamera() const;

protected:
    int m_width;
    int m_height;
    Application* m_app;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<GameWorld> m_world;
    int m_gameState;

};
#endif // SCREEN_H
