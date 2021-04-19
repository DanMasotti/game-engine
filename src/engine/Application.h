#ifndef APPLICATION_H
#define APPLICATION_H
#include "engine/util/CommonIncludes.h"
#include "QKeyEvent"


class Graphics;
class Camera;
class Screen;

class Application
{

public:
    Application();
    virtual ~Application() {};

    void tick(float seconds);

    void draw(Graphics* g);

    // input events
    void onMousePress(QMouseEvent *event, int dx, int dy);

    void onMouseMove(int dx, int dy);

    void onMouseRelease(QMouseEvent* event, int dx, int dy);

    void onMouseWheel(int dx, int dy);

    void onKeyPress(QKeyEvent *event);

    void onKeyRepeat(QKeyEvent *event);

    void onKeyRelease(QKeyEvent *event);

    void resize(int width, int height);

    void removeScreen(QString screenID);

    void addScreen(QString screenID, std::shared_ptr<Screen> screen);

    void switchScreen(QString switchScreenID);

    virtual void reset(int gameState) = 0;

    void setGameState(int gameState);

protected:

    QMap<QString, std::shared_ptr<Screen>> m_screens;
    QString m_currentScreenID;
    int m_gameState;
};

#endif // APPLICATION_H

