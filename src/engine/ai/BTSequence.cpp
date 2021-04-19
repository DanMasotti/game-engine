#include "BTSequence.h"

#include <iostream>

BTSequence::BTSequence(QString id)
{
    m_children = std::vector<std::shared_ptr<BTNode>>();
    m_lastRunning = 0;
    m_id = id;
}


/*
 * Unreal: Sequence nodes execute their children from left to right.
 * They stop executing when one of their children fails.
 * If a child fails, then the Sequence fails.
 * If all the Sequence's children succeed, then the Sequence succeeds.
 */
Status BTSequence::update(float seconds) {

//    std::cout << "==========" << m_id.toStdString() << " has " << m_children.size() << " children ==========" << std::endl;

    for (int i = m_lastRunning, sz = m_children.size(); i < sz; ++i) {

        Status childStatus = m_children[i]->update(seconds);

//        std::cout << "now updating " << m_children[i]->getID().toStdString();
//        std::cout << "... he is " << childStatus << std::endl;

//        m_lastRunning = i;
        if (childStatus == FAIL) {
            reset();
            return FAIL;
        }
//        else if (childStatus == RUNNING) {
//            m_lastRunning = i;
//            return RUNNING;
//        }
    }

    reset();
    return SUCCESS;
}

void BTSequence::reset() {
    m_lastRunning = 0;
    for (int i = 0, sz = m_children.size(); i < sz; ++i) {
        m_children[i]->reset();
    }
}

