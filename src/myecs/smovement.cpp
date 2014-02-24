#include "smovement.h"
#include "cspeed.h"
#include "cposition.h"
#include <cassert>
using namespace ECS;
int SMovement::called = 0;
SMovement::SMovement():System("Movement"),m_cSpeedMap(),m_cPositionMap()
{

}

void SMovement::update()
{
    //    assert(m_cPositionMap);
    for(auto &m : m_entMap)
    {
        if (!m.second)
            continue;
        if(m_listenFunction)
            m_listenFunction();
        ecsint id = m_entityId;
        called++;
    }
    //    std::cout<<"Entity: "<<m_entityId<<std::endl;
    //    if(m_cSpeed)
    //    {
    //        if(m_cPosition->getX() < 500)
    //            m_cPosition->setX(m_cPosition->getX()+m_cSpeed->getX());
    //        if(m_cSpeed->getX() < 5)
    //            m_cSpeed->setX(m_cSpeed->getX()+0.5);
    //    }

    //    std::cout <<m_cPosition->name()<<" X: "<<m_cPosition->getX()<<std::endl<<std::endl;
}

bool SMovement::attachComponent(ecsint eid, Component *comp)
{
    //    bool ret = false;
    //    if(!System::attachComponent(eid,comp))
    //        return false;
    //    if(!m_cSpeed)
    //    {
    //        m_cSpeed = dynamic_cast<CSpeed*>(comp);
    //        ret = true;
    //    }
    //    if(!m_cPosition)
    //    {
    //        m_cPosition = dynamic_cast<CPosition*>(comp);
    //        ret = true;
    //    }

    //    return  ret;
}

bool SMovement::detachComponent(ecsint cid)
{
    //    if(!System::detachComponent(cid))
    //        return false;
    //    bool speed = false;
    //    bool pos = false;
    //    auto it = m_compMap.cbegin();
    //    for(;it!= m_compMap.cend();++it)
    //    {
    //        if(m_cSpeed == it->second)
    //        {
    //            speed = true;
    //        }
    //        if(m_cPosition == it->second)
    //        {
    //            pos = true;
    //        }

    //    }
    //    if(!pos)
    //        m_cPosition = nullptr;
    //    if(!speed)
    //        m_cSpeed = nullptr;
    //    return true;
}

bool SMovement::addEntity(ecsint eid)
{
    if(System::addEntity(eid))
    {
        //        std::cout<<"IN DERIVED"<<std::endl;

        //        auto it = m_cSpeedMap.find(eid);
        //        if(it == m_cSpeedMap.end())
        //        {
        //            m_cSpeedMap.emplace(eid,SpeedUp(new CSpeed()));
        //        }
        //        auto it2 = m_cPositionMap.find(eid);
        //        if(it2 == m_cPositionMap.end())
        //        {
        //            m_cPositionMap.emplace(eid,PositionUp(new CPosition()));
        //        }

    }
}



