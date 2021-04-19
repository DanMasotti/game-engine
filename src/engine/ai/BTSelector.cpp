#include "BTSelector.h"

#include <iostream>

BTSelector::BTSelector(QString id)
{
    m_children = std::vector<std::shared_ptr<BTNode>>();
    m_lastRunning = 0;
    m_id = id;
}

/*
 * Unreal: Selector Nodes execute their children from left to right.
 * They stop executing when one of their children succeeds.
 * If a Selector's child succeeds, the Selector succeeds.
 * If all the Selector's children fail, the Selector fails.
 */
Status BTSelector::update(float seconds) {

//    std::cout << "==========" << m_id.toStdString() << " has " << m_children.size() << " children ==========" << std::endl;

    for (int i = m_lastRunning, sz = m_children.size(); i < sz; ++i) {

        Status childStatus = m_children[i]->update(seconds);
//        std::cout << "now updating " << m_children[i]->getID().toStdString();
//        std::cout << "... he is " << childStatus << std::endl;

//        m_lastRunning = i;
        if (childStatus == SUCCESS) {
            reset();
            return SUCCESS;
        }
//        else if (childStatus == RUNNING) {
//            m_lastRunning = i;
//            return RUNNING;
//        }
    }

    reset();
    return FAIL;
}

void BTSelector::reset() {
    m_lastRunning = 0;
    for (int i = 0, sz = m_children.size(); i < sz; ++i) {
        m_children[i]->reset();
    }
}
