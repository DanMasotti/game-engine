#ifndef BTCOMPOSITE_H
#define BTCOMPOSITE_H

#include "BTNode.h"
#include <vector>

class BTComposite: public BTNode {
public:
    void addChild(std::shared_ptr<BTNode> child) {
        if (m_children.size() == 0) {
            m_children = {child};
        } else {
            m_children.push_back(child);
        }
    }

protected:
    std::vector<std::shared_ptr<BTNode>> m_children;
    int m_lastRunning;
};


#endif // BTCOMPOSITE_H
