#include "smovement-sfmlfull.h"
#include "../Components/cspeed.h"
#include "../Components/cposition.h"
#include <cassert>
using namespace ECS;
unsigned long long SMovement::counter=0;
SMovement::SMovement(ecsint eid, ecsint sid):System(eid,sid),m_cSpeed(),m_cPosition(),m_cAction()
{
    m_name="Movement";
}

void SMovement::update()
{
    //    assert(m_cPosition);
    //    std::cout<<"Entity: "<<m_entityId<<std::endl;
    if(!m_cPosition)
        return;

    counter++;
    ecsint id = m_entityId;

    if(m_cSpeed)
    {
        //        if(m_cPosition->getX() < 500)
        m_cPosition->setX(m_cPosition->getX()+m_cSpeed->getX());
        m_cPosition->setY(m_cPosition->getY()+m_cSpeed->getY());
        if(m_cAction)
        {
            if((m_cAction->getAction("LEFT") && m_cSpeed->getX() > -m_cSpeed->getMx()))
            {
                m_cSpeed->setDx(m_cSpeed->getDx()-0.1);
            }

            if((m_cAction->getAction("RIGHT") && m_cSpeed->getX() < m_cSpeed->getMx()))
            {
                m_cSpeed->setDx(m_cSpeed->getDx()+0.1);
            }

            if((m_cAction->getAction("UP") && m_cSpeed->getY() > -m_cSpeed->getMy()))
            {
                m_cSpeed->setDy(m_cSpeed->getDy()-0.1);
            }

            if((m_cAction->getAction("DOWN") && m_cSpeed->getY() < m_cSpeed->getMy()))
            {
                m_cSpeed->setDy(m_cSpeed->getDy()+0.1);
            }

            if(!m_cAction->getAction("LEFT") && !m_cAction->getAction("RIGHT"))
            {
                m_cSpeed->setDx(0);
            }

            if(!m_cAction->getAction("UP") && !m_cAction->getAction("DOWN"))
            {
                m_cSpeed->setDy(0);
            }

        }
//        if(m_cSpeed->getDx() > 0)
//            m_cSpeed->setDx(m_cSpeed->getDx()-0.01);
//        if(m_cSpeed->getDx() > 0 && m_cSpeed->getDx() < 0.01)
//            m_cSpeed->setDx(0);
//        if(m_cSpeed->getDx() < 0)
//            m_cSpeed->setDx(m_cSpeed->getDx()+0.01);
//        if(m_cSpeed->getDx() < 0 && m_cSpeed->getDx() > -0.01)
//            m_cSpeed->setDx(0);

        if(m_cSpeed->getX() > 0)
            m_cSpeed->setX(m_cSpeed->getX()-0.1);
        if(m_cSpeed->getX() > 0 && m_cSpeed->getX() < 0.1)
            m_cSpeed->setX(0);
        if(m_cSpeed->getX() < 0)
            m_cSpeed->setX(m_cSpeed->getX()+0.1);
        if(m_cSpeed->getX() < 0 && m_cSpeed->getX() > -0.1)
            m_cSpeed->setX(0);

        if(m_cSpeed->getY() > 0)
            m_cSpeed->setY(m_cSpeed->getY()-0.1);
        if(m_cSpeed->getY() > 0 && m_cSpeed->getY() < 0.1)
            m_cSpeed->setY(0);
        if(m_cSpeed->getY() < 0)
            m_cSpeed->setY(m_cSpeed->getY()+0.1);
        if(m_cSpeed->getY() < 0 && m_cSpeed->getY() > -0.1)
            m_cSpeed->setY(0);


        m_cSpeed->setX(m_cSpeed->getX()+m_cSpeed->getDx());
        m_cSpeed->setY(m_cSpeed->getY()+m_cSpeed->getDy());
//        if(m_cSpeed->getX() < m_cSpeed->getMx() && m_cSpeed->getX() > -m_cSpeed->getMx())
//            m_cSpeed->setX(m_cSpeed->getX()+m_cSpeed->getDx());
//        if(m_cSpeed->getY() < m_cSpeed->getMy() && m_cSpeed->getY() > -m_cSpeed->getMy())
//            m_cSpeed->setY(m_cSpeed->getY()+m_cSpeed->getDy());
        //        std::cout << m_cSpeed->name()<<" Speed X: "<<m_cSpeed->getX()<<std::endl;

        //            m_cSpeed->setX(5);
        //        std::cout<<std::endl;
    }

    //    std::cout <<m_cPosition->name()<<" X: "<<m_cPosition->getX()<<std::endl<<std::endl;

    if(m_listenFunction)
        m_listenFunction();
    //    std::cout<<std::endl;
}

bool SMovement::attachComponent(ecsint eid, Component *comp)
{

    if(!m_cSpeed)
    {
        m_cSpeed = dynamic_cast<CSpeed*>(comp);
        if(m_cSpeed)
            return true;
    }
    if(!m_cPosition)
    {
        m_cPosition = dynamic_cast<CPosition*>(comp);
        if(m_cPosition)
            return true;
    }
    if(!m_cAction)
    {
        m_cAction = dynamic_cast<CAction*>(comp);
        if(m_cAction)
            return true;
    }
    return  false;
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
        if(m_cAction == cmp)
        {
            m_cAction = nullptr;
            return true;
        }
    }
    catch(std::out_of_range e)
    {}

    return false;
}



