#include "sbounds-sfmlfull.h"
using namespace ECS;
unsigned long long SBounds::counter=0;
SBounds::SBounds(ecsint eid, ecsint sid):System(eid,sid),m_cPosition(nullptr),m_cSize(nullptr),m_cSpeed(nullptr),m_cBounds(nullptr)
{
}

void SBounds::update()
{
    if(!m_cPosition || !m_cBounds || !m_cSpeed || !m_cSize)
        return;
    counter++;
//    std::cout<<"Bounds update"<<std::endl;
    if(m_cPosition->getX()>m_cBounds->getX1()-m_cSize->getWidth())
    {
        m_cPosition->setX(m_cBounds->getX1()-m_cSize->getWidth());
        m_cSpeed->setX(0);
        m_cSpeed->setDx(-m_cSpeed->getDx());
    }
    else if(m_cPosition->getX()<m_cBounds->getX())
    {
        m_cPosition->setX(m_cBounds->getX());
        m_cSpeed->setX(0);
        m_cSpeed->setDx(-m_cSpeed->getDx());
    }
    if(m_cPosition->getY()>m_cBounds->getY1()-m_cSize->getHeight())
    {
        m_cPosition->setY(m_cBounds->getY1()-m_cSize->getHeight());
        m_cSpeed->setY(0);
        m_cSpeed->setDy(-m_cSpeed->getDy());
    }
    else if(m_cPosition->getY()<m_cBounds->getY())
    {
        m_cPosition->setY(m_cBounds->getY());
        m_cSpeed->setY(0);
        m_cSpeed->setDy(-m_cSpeed->getDy());
    }
//    std::cout<<"Pos X:"<<m_cPosition->getX()<<std::endl;
//    std::cout<<"Pos Y:"<<m_cPosition->getY()<<std::endl;

    if(m_listenFunction)
        m_listenFunction();

}

bool SBounds::attachComponent(ecsint eid, Component *comp)
{
    if(!m_cSize)
    {
        m_cSize = dynamic_cast<CSize*>(comp);
        if(m_cSize)
            return true;
    }
    if(!m_cPosition)
    {
        m_cPosition = dynamic_cast<CPosition*>(comp);
        if(m_cPosition)
            return true;
    }
    if(!m_cBounds)
    {
        m_cBounds = dynamic_cast<CBounds*>(comp);
        if(m_cBounds)
            return true;
    }
    if(!m_cSpeed)
    {
        m_cSpeed = dynamic_cast<CSpeed*>(comp);
        if(m_cSpeed)
            return true;
    }
    return  false;
}

bool SBounds::detachComponent(ecsint cid)
{
    try
    {
        auto cmp = m_cmap->at(cid).get();

        if(m_cSize == cmp)
        {
             m_cSize = nullptr;
             return true;
        }
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



