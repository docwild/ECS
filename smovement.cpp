#include "smovement.h"
#include "cspeed.h"
#include "cposition.h"
#include <cassert>
using namespace ECS;
SMovement::SMovement(const std::string &name, ecsint eid):System(name,eid),m_cSpeed(),m_cPosition()
{
}

void SMovement::update()
{
    assert(m_cPosition);
    std::cout<<"Entity: "<<m_entityId<<std::endl;
    std::cout <<m_cPosition->name()<<" X: "<<m_cPosition->getX()<<std::endl;


    if(m_cSpeed)
    {

        m_cPosition->setX(m_cPosition->getX()+m_cSpeed->getX());
        std::cout << m_cSpeed->name()<<" X: "<<m_cSpeed->getX()<<std::endl;
        m_cSpeed->setX(m_cSpeed->getX()+1);

    }
    std::cout<<std::endl;
}

bool SMovement::attachComponent(ecsint eid, Component *comp)
{
    bool ret = false;
    if(!System::attachComponent(eid,comp))
        return false;
    if(!m_cSpeed)
    {
        m_cSpeed = dynamic_cast<CSpeed*>(comp);
        ret = true;
    }
    if(!m_cPosition)
    {
        m_cPosition = dynamic_cast<CPosition*>(comp);
        ret = true;
    }

    return  ret;
}

bool SMovement::detachComponent(ecsint cid)
{
    if(!System::detachComponent(cid))
        return false;
    bool speed = false;
    bool pos = false;
    auto it = m_compMap.cbegin();
    for(;it!= m_compMap.cend();++it)
    {
        if(m_cSpeed == it->second)
        {
            speed = true;
        }
        if(m_cPosition == it->second)
        {
            pos = true;
        }

    }
    if(!pos)
        m_cPosition = nullptr;
    if(!speed)
        m_cSpeed = nullptr;
    return true;
}

