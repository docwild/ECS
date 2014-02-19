#include "system.h"
using namespace ECS;
System::System(std::string name):m_name(name)
{
}
std::string System::name() const
{
    return m_name;
}

void System::setName(const std::string &name)
{
    m_name = name;
}

