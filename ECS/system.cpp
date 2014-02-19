#include "system.h"
using namespace ECS;
System::System(std::string name, ecsint eid):m_name(name),m_entityId(eid)
{
}

bool System::attachComponent(ecsint cid, Component *comp)
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
std::string System::name() const
{
    return m_name;
}

void System::setName(const std::string &name)
{
    m_name = name;
}
std::unordered_map<ecsint, Component *> System::compMap() const
{
    return m_compMap;
}
ECS::ecsint System::entityId() const
{
    return m_entityId;
}







