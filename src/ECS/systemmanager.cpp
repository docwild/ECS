#include "systemmanager.h"
#include <iostream>
#include <cassert>
using namespace ECS;




SystemManager::SystemManager(const ecsint MAX, const compFactoryFunction &compFact, const sysFactoryFunction &sysFact)
    :MAX(MAX),m_componentMap(),m_systemMap(),m_compFact(compFact),m_sysFact(sysFact)
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
    if(index == MAX)
        return MAX;
    m_entities->setFlags(index,component,m_entities->m_components);
    bool success = true;

    success &= addToMap(component,index,m_compFact,m_componentMap);
    success &= addToMap(systems,index,m_sysFact,m_systemMap);
    for(auto &a: m_systemMap[index])
    {
        addrefs(index,a.second.get());
        for(auto &c: m_componentMap[index])
        {
            attachComponent(a.second.get(),c.first);
        }
    }

    if(success)
        return index;
    return MAX;
}

void SystemManager::update(const std::chrono::duration<double, std::nano> &time_span)
{
    for(auto &sys: m_systemMap)
    {
        //unordered map indexed by entity id of unordered map of systems indexed by system type id
        for(auto &sys2:sys.second)
        {

            //unordered map of systems indexed by system type id
            if(!sys2.second->m_update)
                continue;
            if(sys2.second->m_delay != std::chrono::seconds(0))
            {
                if(sys2.second->m_delayCounter < sys2.second->m_delay )
                {

                    sys2.second->m_delayCounter += time_span;
                    continue;
                }
                //                std::cout<<"delay:"<<time_span.count()<<std::endl;
                //                std::cout<<"delaycout "<<sys2.second->m_delayCounter.count()<<std::endl;
                //                std::cout<<"mdelay "<<sys2.second->m_delay.count()<<std::endl<<std::endl;
                sys2.second->m_delayCounter = std::chrono::seconds(0);
            }

            sys2.second->update();
        }

    }

}

void SystemManager::setSystemUpdate(bool update,ECS::ecsint sysid,ECS::ecsint eid)
{
    getSystem(eid,sysid)->m_update = update;
}

bool SystemManager::attachComponent(System *sys, const ecsint cid)
{
    Component *c = getComponent(sys->entityId(),cid);
    if(!c)
    {
        if(!addToMap(cid,sys->entityId(),m_compFact,m_componentMap))
            return false;
        if(!(c = getComponent(sys->entityId(),cid)))
            return false;
    }
    return sys->attachComponent(cid,c);
}

bool SystemManager::detachComponent(System *sys, const ecsint cid)
{
    return sys->detachComponent(cid);
}

ecsint SystemManager::entityCount()
{
    return m_entities->m_components.size();
}

Component *SystemManager::getComponent(const ecsint eid, const ecsint cid)
{
    return m_componentMap[eid][cid].get();
}

System *SystemManager::getSystem(const ecsint eid, const ecsint id)
{
    return m_systemMap[eid][id].get();
}



