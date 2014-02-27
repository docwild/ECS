#include "caction.h"
using namespace ECS;
CAction::CAction(ecsint id, ecsint cid):Component(id,cid),m_actions()
{
}

const bool CAction::getAction(const std::string &index)
{
    try
    {
        return m_actions.at(index);
    }
    catch(std::out_of_range e)
    {
        return false;
    }
}

void CAction::setActions(const std::string index, bool value)
{
    m_actions[index] = value;
}
