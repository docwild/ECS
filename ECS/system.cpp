#include "system.h"
using namespace ECS;
System::System(std::string name, ecsint eid):m_name(name),m_entityId(eid)
{
}

void System::attachComponent(ecsint eid, Component *comp)
{
    m_compMap[eid] = comp;
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







