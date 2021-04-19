#ifndef BTOREINTATEACTION_H
#define BTOREINTATEACTION_H

#include "engine/ai/BTAction.h"

class BTOreintateAction: public BTAction
{
public:
    BTOreintateAction(AIComponent* comp, QString target);

    virtual Status update(float seconds) override;
    virtual void reset() override;

private:
    QString m_target;
};

#endif // BTOREINTATEACTION_H
