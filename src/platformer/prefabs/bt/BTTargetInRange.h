#ifndef BTTARGETINRANGE_H
#define BTTARGETINRANGE_H

#include "engine/ai/BTCondition.h"

#include "QString"


class AIComponent;

class BTTargetInRangeCondition: public BTCondition
{
public:
    BTTargetInRangeCondition(AIComponent* comp, QString target, float radius = 1.f);

    virtual Status update(float seconds) override;
    virtual void reset() override;

private:
    float m_radius;
    QString m_target;
};

#endif // BTTARGETINRANGE_H
