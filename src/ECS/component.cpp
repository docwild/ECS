#include "component.h"
using namespace ECS;
Component::Component(const std::string &name, ECS::ecsint eid):m_name(name)
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
