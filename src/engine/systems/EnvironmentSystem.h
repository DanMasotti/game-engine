#ifndef ENVIRONMENTSYSTEM_H
#define ENVIRONMENTSYSTEM_H

#include "System.h"
#include "../graphics/obj.h"
#include "../util/SparseSpatialGrid.h"

class EnvironmentSystem: public System
{
public:
    EnvironmentSystem(QString worldMesh, QString navMesh);

    virtual void onTick(float seconds) override;

private:
    void detect();

    std::shared_ptr<OBJ> m_environment;
    std::shared_ptr<OBJ> m_navMesh;
    std::shared_ptr<SparseSpatialGrid<OBJ::Triangle*>> m_grid;
};

#endif // ENVIRONMENTSYSTEM_H
