#include "system.h"
using namespace ECS;
System::System(const std::string &name, ecsint eid):m_name(name),m_entityId(eid)
{
    std::cout<<"constructing system"<<std::endl;
}

bool System::attachComponent(ecsint cid,  Component *comp)
{
    auto it = m_compMap.find(cid);
    if(it == m_compMap.end())
    {
        m_compMap[cid] = comp;
        return true;
    }
    return false;
}

bool System::detachComponent(ecsint cid)
{
    //    m_compMap[cid] = nullptr;
    auto it = m_compMap.find(cid);
    if(it != m_compMap.end())
    {
        m_compMap.erase(it);
        return true;
    }
    return false;


}
const std::string &System::name() const
{
    return m_name;
}

void System::addListener(System::listype func)
{
    m_listenFunction = func;
}

void System::setName(const std::string &name)
{
    m_name = name;
}
const std::unordered_map<ecsint, Component *> &System::compMap() const
{
    return m_compMap;
}
const ecsint System::entityId() const
{
    return m_entityId;
}







