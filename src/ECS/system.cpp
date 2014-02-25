#include "system.h"
using namespace ECS;
System::System(ecsint eid, ecsint sid):m_entityId(eid),m_systemId(sid)
{
}
const System::CompMap * const System::cmap() const
{
    return m_cmap;
}

void System::setCmap(CompMap *cmap)
{
    m_cmap = cmap;
}



const std::string &System::name() const
{
    return m_name;
}

void System::addListener(System::listype func)
{
    m_listenFunction = std::move(func);
}

void System::setName(const std::string &name)
{
    m_name = name;
}

const ecsint System::entityId() const
{
    return m_entityId;
}







