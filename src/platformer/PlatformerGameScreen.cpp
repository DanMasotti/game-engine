#include "PlatformerGameScreen.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/Application.h"

#include "engine/GameWorld.h"
#include "engine/components/PlayerControlComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/HealthComponent.h"
#include "engine/systems/DrawSystem.h"
#include "engine/systems/CollisionSystem.h"
#include "engine/systems/TickSystem.h"
#include "engine/systems/EnvironmentSystem.h"
#include "engine/systems/AISystem.h"

#include "prefabs/PlatformerEnvironment.h"
#include "prefabs/PlatformerPlayer.h"
#include "prefabs/PlatformerEnemy.h"
#include "prefabs/Rat.h"
#include "prefabs/Barrel.h"

#include "engine/graphics/ResourceLoader.h"
#include "engine/graphics/Shape.h"

#include "engine/components/AIComponent.h"

#include "engine/components/AnimationComponent.h"
#include "engine/systems/AnimationSystem.h"

#include "engine/components/DrawableComponent.h"

#include "engine/util/RNG.h"

using namespace Platformer;

GameScreen::GameScreen(Application* app, std::shared_ptr<Camera> cam):
    Screen(app, cam)
{
    m_world = std::make_shared<GameWorld>(this, ":/meshes/level_island.obj", ":/meshes/level_island_navmesh.obj");
    Graphics* g = Graphics::getGlobalInstance();
    loadAnimations();

    std::shared_ptr<AISystem> aiSys = std::make_shared<AISystem>(":/meshes/level_island_navmesh.obj", m_world.get());
    m_world->addSystem<AISystem>(std::move(aiSys));

    std::shared_ptr<Environment> env = std::make_shared<Environment>(m_world.get(), "terrain");

    std::shared_ptr<Player> player = std::make_shared<Player>(m_world.get());

    Material ratMat;
    g->addTexture("ratMat", ":/images/rat_tex.png");
    ratMat.textureName = "ratMat";
    g->addMaterial("ratMat", ratMat);

    Material ghoulMat;
    g->addTexture("ghoulMat", ":/images/ghoul-tex.png");
    ghoulMat.textureName = "ghoulMat";
    g->addMaterial("ghoulMat", ghoulMat);

    const RNG rng = RNG();

    Material rust;
    g->addTexture("rust", ":/images/rust.png");
    rust.textureName = "rust";
    g->addMaterial("rust", rust);

    const int M = 3;
    const int N = 2;
    for (int m = 0; m < M; ++m) {
        for (int n = 0; n < N; ++n) {
            const int index = n + m*N;
            QString id = QString::fromStdString("rat_" + std::to_string(index));

            const float xLoc = M - m + rng.getRandomNumber()*20.f;
            const float zLoc = N - n + rng.getRandomNumber()*20.f - 25.f;

            std::shared_ptr<Rat> rat = std::make_shared<Rat>(m_world.get(),
                                                                   id,
                                                                   glm::vec3(xLoc, 20.f, zLoc));

            m_world->addGameObject(id, rat);
        }
    }


    const int R = 2;
    const int C = 2;
    for (int i = 0; i < R; ++i){
        for (int j = 0; j < C; ++j) {
            const int index = i + j*C;
            QString id = QString::fromStdString("ghoul_" + std::to_string(index));

            const float xLoc = R - i + rng.getRandomNumber()*20.f;
            const float zLoc = C - j + rng.getRandomNumber()*20.f - 25.f;

            for (int k = 0; k < 2; ++k) {
                QString postId = QString::fromStdString("ghoul_" + std::to_string(index) + "_post_" + std::to_string(k));

                glm::vec3 postPos;
                switch (k) {
                case 0:
                    postPos = glm::vec3(xLoc + 2, 20, zLoc - 2);
                    break;
                case 1:
                    postPos = glm::vec3(xLoc - 2, 20, zLoc + 2);
                    break;
                }

                std::shared_ptr<Barrel> post = std::make_shared<Barrel>(m_world.get(), postId, postPos);
                m_world->addGameObject(postId, post);
            }

            std::shared_ptr<Enemy> ghoul = std::make_shared<Enemy>(m_world.get(), id, glm::vec3(xLoc, 20.f, zLoc));
            m_world->addGameObject(id, ghoul);
        }
    }


//    {
//        const int index = 0;
//        QString id = QString::fromStdString("ghoul_" + std::to_string(index));

//        const float xLoc = 20;
//        const float zLoc = -20;

//        for (int k = 0; k < 2; ++k) {
//            QString postId = QString::fromStdString("ghoul_" + std::to_string(index) + "_post_" + std::to_string(k));

//            glm::vec3 postPos;
//            switch (k) {
//            case 0:
//                postPos = glm::vec3(15, 20, -15);
//                break;
//            case 1:
//                postPos = glm::vec3(30, 20, -15);
//                break;
//            }

//            std::shared_ptr<Barrel> post = std::make_shared<Barrel>(m_world.get(), postId, postPos);
//            m_world->addGameObject(postId, post);
//        }

//        std::shared_ptr<Enemy> ghoul = std::make_shared<Enemy>(m_world.get(), id, glm::vec3(xLoc, 20.f, zLoc));
//        m_world->addGameObject(id, ghoul);
//    }


//    {
//        const int index = 1;
//        QString id = QString::fromStdString("ghoul_" + std::to_string(index));

//        const float xLoc = -15;
//        const float zLoc = -20;

//        for (int k = 0; k < 2; ++k) {
//            QString postId = QString::fromStdString("ghoul_" + std::to_string(index) + "_post_" + std::to_string(k));

//            glm::vec3 postPos;
//            switch (k) {
//            case 0:
//                postPos = glm::vec3(0, 50, -10);
//                break;
//            case 1:
//                postPos = glm::vec3(0, 50, -35);
//                break;
//            }

//            std::shared_ptr<Barrel> post = std::make_shared<Barrel>(m_world.get(), postId, postPos);
//            m_world->addGameObject(postId, post);
//        }

//        std::shared_ptr<Enemy> ghoul = std::make_shared<Enemy>(m_world.get(), id, glm::vec3(xLoc, 20.f, zLoc));
//        m_world->addGameObject(id, ghoul);
//    }

//    {
//        const int index = 1;
//        QString id = QString::fromStdString("ghoul_" + std::to_string(index));

//        const float xLoc = -10;
//        const float zLoc = -20;

//        for (int k = 0; k < 2; ++k) {
//            QString postId = QString::fromStdString("ghoul_" + std::to_string(index) + "_post_" + std::to_string(k));

//            glm::vec3 postPos;
//            switch (k) {
//            case 0:
//                postPos = glm::vec3(20, 50, -10);
//                break;
//            case 1:
//                postPos = glm::vec3(0, 50, -25);
//                break;
//            }

//            std::shared_ptr<Barrel> post = std::make_shared<Barrel>(m_world.get(), postId, postPos);
//            m_world->addGameObject(postId, post);
//        }

//        std::shared_ptr<Enemy> ghoul = std::make_shared<Enemy>(m_world.get(), id, glm::vec3(xLoc, 20.f, zLoc));
//        m_world->addGameObject(id, ghoul);
//    }

//    {
//        const int index = 2;
//        QString id = QString::fromStdString("ghoul_" + std::to_string(index));

//        const float xLoc = 30;
//        const float zLoc = -30;

//        for (int k = 0; k < 2; ++k) {
//            QString postId = QString::fromStdString("ghoul_" + std::to_string(index) + "_post_" + std::to_string(k));

//            glm::vec3 postPos;
//            switch (k) {
//            case 0:
//                postPos = glm::vec3(10, 50, -10);
//                break;
//            case 1:
//                postPos = glm::vec3(10, 50, -25);
//                break;
//            }

//            std::shared_ptr<Barrel> post = std::make_shared<Barrel>(m_world.get(), postId, postPos);
//            m_world->addGameObject(postId, post);
//        }

//        std::shared_ptr<Enemy> ghoul = std::make_shared<Enemy>(m_world.get(), id, glm::vec3(xLoc, 20.f, zLoc));
//        m_world->addGameObject(id, ghoul);
//    }


    Material playerMat;
    g->addTexture("player", ":/images/player-tex.png");
    playerMat.textureName = "player";
    g->addMaterial("player", playerMat);

    m_world->addGameObject("terrain", env);
    m_world->addGameObject("player", player);
}


void GameScreen::loadAnimations() {
    Graphics* g = Graphics::getGlobalInstance();

    for (int i = 0; i < 20; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("run_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        QString qstringed = QString::fromStdString(":/meshes/run_" + paddedNum + ".obj");

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("run_" + num, shape);
    }

    for (int i = 0; i < 21; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("strafe_right_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        QString qstringed = QString::fromStdString(":/meshes/strafe_right_" + paddedNum + ".obj");

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("strafe_right_" + num, shape);
    }

    for (int i = 0; i < 21; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("strafe_left_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        QString qstringed = QString::fromStdString(":/meshes/strafe_left_" + paddedNum + ".obj");

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("strafe_left_" + num, shape);
    }

    for (int i = 0; i < 60; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("idle_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/idle_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("idle_" + num, shape);
    }

    for (int i = 16; i < 46; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("jump_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/jump_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("jump_" + num, shape);
    }

    for (int i = 0; i < 31; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("punch_right_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/punch_right_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("punch_right_" + num, shape);
    }

    for (int i = 0; i < 31; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("punch_left_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/punch_left_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("punch_left_" + num, shape);
    }

    for (int i = 0; i < 46; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("kick_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/kick_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("kick_" + num, shape);
    }

    for (int i = 0; i < 43; ++i) {
        std::string num = std::to_string(i + 1);
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("hit_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num;
        std::string filename = ":/meshes/hit_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("hit_" + num, shape);

    }

    for (int i = 0; i < 25; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_run_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        QString qstringed = QString::fromStdString(":/meshes/ghoul_run_" + paddedNum + ".obj");

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_run_" + num, shape);
    }

    for (int i = 0; i < 6; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3

        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_idle_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/ghoul_idle_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_idle_" + num, shape);
    }

    for (int i = 0; i < 80; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_punch_right_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/ghoul_punch_R_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_punch_right_" + num, shape);
    }

    for (int i = 0; i < 80; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_punch_left_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/ghoul_punch_L_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_punch_left_" + num, shape);
    }

    for (int i = 0; i < 61; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_hit_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/ghoul_hit_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_hit_" + num, shape);
    }

    for (int i = 0; i < 85; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("ghoul_scream_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/ghoul_scream_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("ghoul_scream_" + num, shape);
    }

    std::string num = std::to_string(1); // 10 | 3
    std::shared_ptr<Shape> shape = std::make_shared<Shape>("rat_idle_" + num);

    std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
    std::string filename = ":/meshes/rat_idle_" + paddedNum + ".obj";

    QString qstringed = QString::fromStdString(filename);

    ResourceLoader::readObj(qstringed, shape);
    g->addShape("rat_idle_" + num, shape);

    for (int i = 0; i < 10; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        std::shared_ptr<Shape> shape = std::make_shared<Shape>("rat_run_" + num);

        std::string paddedNum = std::string(6 - num.length(), '0') + num; // 000010 | 000003
        std::string filename = ":/meshes/rat_run_" + paddedNum + ".obj";

        QString qstringed = QString::fromStdString(filename);

        ResourceLoader::readObj(qstringed, shape);
        g->addShape("rat_run_" + num, shape);
    }
}




