#ifndef BTNODE_H
#define BTNODE_H

#include "QString"

enum Status {
    SUCCESS,
    FAIL,
    RUNNING
};


class BTNode
{
public:
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;
    QString getID() {
        return m_id;
    }

protected:
    QString m_id;
};

#endif // BTNODE_H
