#include "sdraw.h"
using namespace ECS;
unsigned long long SDraw::counter=0;
SDraw::SDraw(ECS::ecsint eid, ecsint sid):System(eid,sid),m_cSize(nullptr),m_cPosition(nullptr),m_rectShape(nullptr)
{
}

void SDraw::update()
{
    if(!m_cPosition || !m_rectShape)
        return;
//    std::cout<<"Draw"<<std::endl;

//    m_win->clear();

    if(m_lifetime == 0)
    {
        auto it = m_drMap->find(m_entityId);
        if(it != m_drMap->end())
            m_drMap->erase(it);
        return;
    }
    m_rectShape->setPosition(m_cPosition->getX(),m_cPosition->getY());
    m_lifetime--;
//    m_win->display();
    if(m_listenFunction)
        m_listenFunction();
}

bool SDraw::attachComponent(ecsint eid, Component *comp)
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

    return  false;
}

bool SDraw::detachComponent(ecsint cid)
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
    }
    catch(std::out_of_range e)
    {}

    return false;
}

void SDraw::makeRect()
{
    if(m_cSize && m_cPosition && !m_rectShape)
    {
//        std::cout<<"no rect"<<std::endl;
        m_rectShape.reset(new sf::RectangleShape(sf::Vector2f(m_cSize->getWidth(),m_cSize->getHeight())));
    }
}
