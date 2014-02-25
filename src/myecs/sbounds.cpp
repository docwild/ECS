#include "sbounds.h"
using namespace ECS;
SBounds::SBounds(ecsint eid):System(eid),m_cPosition()
{
}

void SBounds::update()
{
    if(!m_cPosition || !m_cBounds || !m_cSpeed)
        return;
    std::cout<<"Bounds update"<<std::endl;
    if(m_cPosition->getX()>m_cBounds->getX1())
    {
        m_cPosition->setX(m_cBounds->getX1());
        m_cSpeed->setX(0);
        m_cSpeed->setDx(-m_cSpeed->getDx());
    }
    if(m_cPosition->getX()<m_cBounds->getX())
    {
        m_cPosition->setX(m_cBounds->getX());
        m_cSpeed->setX(0);
        m_cSpeed->setDx(-m_cSpeed->getDx());
    }
    if(m_cPosition->getY()>m_cBounds->getY1())
    {
        m_cPosition->setY(m_cBounds->getY1());
        m_cSpeed->setY(0);
        m_cSpeed->setDy(-m_cSpeed->getDy());
    }
    if(m_cPosition->getY()<m_cBounds->getY())
    {
        m_cPosition->setY(m_cBounds->getY());
        m_cSpeed->setY(0);
        m_cSpeed->setDy(-m_cSpeed->getDy());
    }
    std::cout<<"Pos X:"<<m_cPosition->getX()<<std::endl;
    std::cout<<"Pos Y:"<<m_cPosition->getY()<<std::endl;



}

bool SBounds::attachComponent(ecsint eid, Component *comp)
{
    bool ret = false;
    if(!m_cPosition)
    {
        m_cPosition = dynamic_cast<CPosition*>(comp);
        ret = true;
    }
    if(!m_cBounds)
    {
        m_cBounds = dynamic_cast<CBounds*>(comp);
        ret = true;
    }
    if(!m_cSpeed)
    {
        m_cSpeed = dynamic_cast<CSpeed*>(comp);
        ret = true;
    }
    return  ret;
}

bool SBounds::detachComponent(ecsint cid)
{
    try
    {
        auto cmp = m_cmap->at(cid).get();
        if(m_cPosition == cmp)
        {
            m_cPosition = nullptr;
            return true;
        }
        if(m_cBounds == cmp)
        {
            m_cBounds = nullptr;
            return true;
        }
        if(m_cSpeed == cmp)
        {
             m_cSpeed = nullptr;
             return true;
        }
    }
    catch(std::out_of_range e)
    {}

    return false;
}



