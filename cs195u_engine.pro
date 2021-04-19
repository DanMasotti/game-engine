QT += core gui opengl widgets

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17
CONFIG += c++17

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++17
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/engine/Application.cpp \
    src/engine/GameObject.cpp \
    src/engine/GameWorld.cpp \
    src/engine/Screen.cpp \
    src/engine/ai/BTSelector.cpp \
    src/engine/ai/BTSequence.cpp \
    src/engine/ai/Blackboard.cpp \
    src/engine/components/AIComponent.cpp \
    src/engine/components/AnimationComponent.cpp \
    src/engine/components/CollisionComponent.cpp \
    src/engine/components/CollisionResponseComponent.cpp \
    src/engine/components/Component.cpp \
    src/engine/components/DrawableComponent.cpp \
    src/engine/components/EnvironmentCollisionComponent.cpp \
    src/engine/components/HealthComponent.cpp \
    src/engine/components/PhysicsComponent.cpp \
    src/engine/components/PlayerControlComponent.cpp \
    src/engine/components/TransformComponent.cpp \
    src/engine/components/UIComponent.cpp \
    src/engine/graphics/obj.cpp \
    src/engine/systems/AISystem.cpp \
    src/engine/systems/AnimationSystem.cpp \
    src/engine/systems/CollisionSystem.cpp \
    src/engine/systems/DrawSystem.cpp \
    src/engine/systems/EnvironmentSystem.cpp \
    src/engine/systems/PhysicsSystem.cpp \
    src/engine/systems/System.cpp \
    src/engine/systems/TickSystem.cpp \
    src/engine/systems/UISystem.cpp \
    src/engine/util/RNG.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/platformer/PlatformerGame.cpp \
    src/platformer/PlatformerGameScreen.cpp \
    src/platformer/PlatformerMenuScreen.cpp \
    src/platformer/prefabs/Barrel.cpp \
    src/platformer/prefabs/PlatformerEnemy.cpp \
    src/platformer/prefabs/PlatformerEnvironment.cpp \
    src/platformer/prefabs/PlatformerPlayer.cpp \
    src/platformer/prefabs/Rat.cpp \
    src/platformer/prefabs/bt/BTChaseSequence.cpp \
    src/platformer/prefabs/bt/BTCombatSequence.cpp \
    src/platformer/prefabs/bt/BTExecutePathAction.cpp \
    src/platformer/prefabs/bt/BTGhoul.cpp \
    src/platformer/prefabs/bt/BTMeleeAction.cpp \
    src/platformer/prefabs/bt/BTOreintateAction.cpp \
    src/platformer/prefabs/bt/BTPatrolSequence.cpp \
    src/platformer/prefabs/bt/BTPlanPathAction.cpp \
    src/platformer/prefabs/bt/BTRandomWalk.cpp \
    src/platformer/prefabs/bt/BTRat.cpp \
    src/platformer/prefabs/bt/BTScreamAction.cpp \
    src/platformer/prefabs/bt/BTTargetInRange.cpp \
    src/platformer/prefabs/bt/BTWaitAction.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/engine/Application.h \
    src/engine/Data.h \
    src/engine/GameObject.h \
    src/engine/GameWorld.h \
    src/engine/Screen.h \
    src/engine/ai/BTAction.h \
    src/engine/ai/BTComposite.h \
    src/engine/ai/BTCondition.h \
    src/engine/ai/BTNode.h \
    src/engine/ai/BTSelector.h \
    src/engine/ai/BTSequence.h \
    src/engine/ai/Blackboard.h \
    src/engine/ai/Graph.h \
    src/engine/components/AIComponent.h \
    src/engine/components/AnimationComponent.h \
    src/engine/components/CollisionComponent.h \
    src/engine/components/CollisionResponseComponent.h \
    src/engine/components/Component.h \
    src/engine/components/DrawableComponent.h \
    src/engine/components/EnvironmentCollisionComponent.h \
    src/engine/components/HealthComponent.h \
    src/engine/components/PhysicsComponent.h \
    src/engine/components/PlayerControlComponent.h \
    src/engine/components/TransformComponent.h \
    src/engine/components/UIComponent.h \
    src/engine/graphics/obj.h \
    src/engine/physics/CollisionUtils.h \
    src/engine/systems/AISystem.h \
    src/engine/systems/AnimationSystem.h \
    src/engine/systems/CollisionSystem.h \
    src/engine/systems/DrawSystem.h \
    src/engine/systems/EnvironmentSystem.h \
    src/engine/systems/PhysicsSystem.h \
    src/engine/systems/System.h \
    src/engine/systems/TickSystem.h \
    src/engine/systems/UISystem.h \
    src/engine/util/RNG.h \
    src/engine/util/SparseSpatialGrid.h \
    src/engine/util/TypeMap.h \
    src/mainwindow.h \
    src/platformer/PlatformerGame.h \
    src/platformer/PlatformerGameScreen.h \
    src/platformer/PlatformerMenuScreen.h \
    src/platformer/prefabs/Barrel.h \
    src/platformer/prefabs/PlatformerEnemy.h \
    src/platformer/prefabs/PlatformerEnvironment.h \
    src/platformer/prefabs/PlatformerPlayer.h \
    src/platformer/prefabs/Rat.h \
    src/platformer/prefabs/bt/BTChaseSequence.h \
    src/platformer/prefabs/bt/BTCombatSequence.h \
    src/platformer/prefabs/bt/BTExecutePathAction.h \
    src/platformer/prefabs/bt/BTGhoul.h \
    src/platformer/prefabs/bt/BTMeleeAction.h \
    src/platformer/prefabs/bt/BTOreintateAction.h \
    src/platformer/prefabs/bt/BTPatrolSequence.h \
    src/platformer/prefabs/bt/BTPlanPathAction.h \
    src/platformer/prefabs/bt/BTRandomWalk.h \
    src/platformer/prefabs/bt/BTRat.h \
    src/platformer/prefabs/bt/BTScreamAction.h \
    src/platformer/prefabs/bt/BTTargetInRange.h \
    src/platformer/prefabs/bt/BTWaitAction.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h

FORMS += src/mainwindow.ui

RESOURCES += \
    res/meshes/meshes.qrc \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag

INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
