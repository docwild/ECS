#include "systemmanager.h"
#include <iostream>
#include <cassert>
using namespace ECS;




SystemManager::SystemManager(const ecsint MAX, const compFactoryFunction &compFact, const sysFactoryFunction &sysFact)
    :MAX(MAX),m_compFact(compFact),m_sysFact(sysFact)
{
    m_entities.reset( new Entities(MAX));
}

SystemManager::~SystemManager()
{


}







const ecsint SystemManager::addEntity(const ecsint &systems, const ecsint &component)
{
    if(component == 0)
        return MAX;
    ecsint index = m_entities->addEntity(component);
    if(index > MAX)
        return index;
    m_entities->setComponents(index,component);
    bool success = true;
    success &= addSystems(systems,index);
    //    registerType(component,index,m_compsMap,m_compFact);
    success &= addComponents(component,index);

    //    success &= addToMap(component,index,m_compTypes,m_compFact,m_componentMap);
    //    success &= addToMap(systems,index,m_sysTypes,m_sysFact,m_systemMap);
    if(success)
        return index;
    return MAX+1;
}

void SystemManager::update(const std::chrono::duration<double, std::nano> &time_span)
{
    for(auto &sys: m_systemsMap)
    {


        //unordered map of systems indexed by system type id
        if(!sys.second->m_update)
            continue;
        if(sys.second->m_delay != std::chrono::seconds(0))
        {
            if(sys.second->m_delayCounter < sys.second->m_delay )
            {

                sys.second->m_delayCounter += time_span;
                continue;
            }
            //                std::cout<<"delay:"<<time_span.count()<<std::endl;
            //                std::cout<<"delaycout "<<sys2.second->m_delayCounter.count()<<std::endl;
            //                std::cout<<"mdelay "<<sys2.second->m_delay.count()<<std::endl<<std::endl;
            sys.second->m_delayCounter = std::chrono::seconds(0);
        }

        sys.second->update();
    }



}

void SystemManager::setSystemUpdate(bool update,ECS::ecsint sysid,ECS::ecsint eid)
{
    getSystem(eid,sysid)->m_update = update;
}

bool SystemManager::attachComponent(ecsint cid, ecsint eid)
{
    compMapUP *comps;
    try
    {
        comps = &m_compsMap.at(eid);


    }
    catch(std::out_of_range e)
    {
        addComponents(cid,eid);
        comps = &m_compsMap.at(eid);
    }
    auto it = comps->find(cid);
    if(it != comps->end() && it->second)
    {
        //            std::cout<<"Got it"<<std::endl;
        m_compsAttached.at(eid)[cid] = true;
        return true;
    }
    return false;

}

//bool SystemManager::attachComponent(System *sys, const ecsint cid)
//{
//    Component *c = getComponent(sys->entityId(),cid);
//    assert(c);
//    if(!c)
//        return false;
//    return sys->attachComponent(cid,c);
//}

//bool SystemManager::detachComponent(System *sys, const ecsint cid)
//{
//    //    std::cout <<"detached "<<cid<<std::endl;
//    return sys->detachComponent(cid);
//}

SystemManager::hilow SystemManager::bounds(ecsint num)
{
    if (!num)
        return hilow();

    ECS::ecsint hb = 1;
    ECS::ecsint lb = 0;
    ECS::ecsint tmp = num;
    while (tmp >>= 1)
        hb <<= 1;
    for(int x = 1; x <= hb; x *=2)
    {
        if((x & num) == x)
        {
            lb = x;
            break;
        }
    }
    hilow ret;
    ret["high"]=hb;
    ret["low"]=lb;
    return ret;
}

ecsint SystemManager::entityCount()
{
    return m_entities->m_components.size();
}

Component *SystemManager::getComponent(const ecsint eid, const ecsint cid)
{
    return m_compsMap[eid][cid].get();
}

System *SystemManager::getSystem(const ecsint eid, const ecsint id)
{
    if(m_systemsMap[id]->hasSystem(eid))
        return m_systemsMap[id].get();
    return nullptr;
}



