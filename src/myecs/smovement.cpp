#include "smovement.h"
#include "cspeed.h"
#include "cposition.h"
#include <cassert>
using namespace ECS;
SMovement::SMovement(ecsint eid):System(eid),m_cSpeed(),m_cPosition()
{
    m_name="Movement";
}

void SMovement::update()
{
    //    assert(m_cPosition);
    std::cout<<"Entity: "<<m_entityId<<std::endl;
    if(!m_cPosition)
        return;


    ecsint id = m_entityId;

    if(m_cSpeed)
    {
        if(m_cPosition->getX() < 500)
            m_cPosition->setX(m_cPosition->getX()+m_cSpeed->getX());
        if(m_cSpeed->getX() < 5)
            m_cSpeed->setX(m_cSpeed->getX()+0.5);
        std::cout << m_cSpeed->name()<<" Speed X: "<<m_cSpeed->getX()<<std::endl;

        //            m_cSpeed->setX(5);
        //        std::cout<<std::endl;
    }

    //    std::cout <<m_cPosition->name()<<" X: "<<m_cPosition->getX()<<std::endl<<std::endl;

    if(m_listenFunction)
        m_listenFunction();
    std::cout<<std::endl;
}

bool SMovement::attachComponent(ecsint eid, Component *comp)
{
    bool ret = false;
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
    try
    {
        auto cmp = m_cmap->at(cid).get();
        if(m_cSpeed == cmp)
        {
             m_cSpeed = nullptr;
             return true;
        }
        if(m_cPosition == cmp)
        {
            m_cPosition = nullptr;
            return true;
        }
    }
    catch(std::out_of_range e)
    {}

    return false;
}



