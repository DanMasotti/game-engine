#ifndef BTSELECTOR_H
#define BTSELECTOR_H

#include "BTComposite.h"

#include "QString"

class BTSelector: public BTComposite
{
public:
    BTSelector(QString id);
    virtual ~BTSelector() {};

    virtual Status update(float seconds) override;
    virtual void reset() override;   
};

#endif // BTSELECTOR_H
