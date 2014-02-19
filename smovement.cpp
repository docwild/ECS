#include "smovement.h"
#include "cspeed.h"
#include "cposition.h"
#include <cassert>
using namespace ECS;
SMovement::SMovement(std::string name, ecsint eid):System(name,eid)
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

void SMovement::attachComponent(ecsint eid, Component *comp)
{
    System::attachComponent(eid,comp);
    if(!m_cSpeed)
    {
        m_cSpeed = dynamic_cast<CSpeed*>(comp);
    }
    if(!m_cPosition)
    {
        m_cPosition = dynamic_cast<CPosition*>(comp);
    }
}
