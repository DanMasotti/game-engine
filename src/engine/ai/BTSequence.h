#ifndef BTSEQUENCE_H
#define BTSEQUENCE_H
#include "BTComposite.h"

#include "QString"

class BTSequence: public BTComposite
{
public:
    BTSequence(QString id);
    virtual ~BTSequence() {};

    virtual Status update(float seconds) override;
    virtual void reset() override;
};

#endif // BTSEQUENCE_H
