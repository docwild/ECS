#include "component.h"
using namespace ECS;
Component::Component(ECS::ecsint eid, ecsint cid):m_componentId(cid)
{
}
std::string Component::name() const
{
    return m_name;
}

void Component::setName(const std::string &name)
{
    m_name = name;
}


//void Component::poly()
//{

//}
