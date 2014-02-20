#include "systemmanager.h"
#include <iostream>
#include <cassert>
using namespace ECS;


SystemManager::SystemManager(const ecsint MAX):MAX(MAX),m_componentMap(),m_systemMap(),m_compTypes(),m_sysTypes()
{
    m_entities.reset( new Entities(MAX));
}

SystemManager::~SystemManager()
{


}

const SystemManager::sysMap &SystemManager::systemMap() const
{
    return m_systemMap;
}

SystemManager::sysMap &SystemManager::systemMap()
{
    return const_cast<SystemManager::sysMap&>(static_cast<const SystemManager*>(this)->systemMap());
}

const SystemManager::compMap &SystemManager::componentMap() const
{
    return m_componentMap;
}

SystemManager::compMap &SystemManager::componentMap()
{
    return const_cast<SystemManager::compMap&>(static_cast<const SystemManager*>(this)->componentMap());
}
const SystemManager::registerMap &SystemManager::compTypes() const
{
    return m_compTypes;
}

SystemManager::registerMap &SystemManager::compTypes()
{
    return const_cast<SystemManager::registerMap&>(static_cast<const SystemManager*>(this)->compTypes());
}


const SystemManager::registerMap &SystemManager::sysTypes() const
{
    return m_sysTypes;
}

SystemManager::registerMap &SystemManager::sysTypes()
{
    return const_cast<SystemManager::registerMap&>(static_cast<const SystemManager*>(this)->sysTypes());
}





const ecsint SystemManager::addEntity(const ecsint &systems, const ecsint &component, const compFactoryFunction &cf, const sysFactoryFunction &sf)
{
    if(component == 0)
        return MAX;
    ecsint index = m_entities->addEntity(component);
    if(index == MAX)
        throw MAX;
    m_entities->setComponents(index,component);
    bool success = true;
    success &= addToMap(component,index,m_compTypes,cf,m_componentMap);
    success &= addToMap(systems,index,m_sysTypes,sf,m_systemMap);
    if(success)
        return index;
    return MAX;
}

void SystemManager::update(const double delay)
{
    for(auto &sys: m_systemMap)
    {

//        std::cout<<"update "<<sys.first<<std::endl;
        for(auto &sys2:sys.second)
        {

            if(sys2.second->m_delayCounter < sys2.second->m_delay && sys2.second->m_delay != 0)
            {
                sys2.second->m_delayCounter += delay;
                continue;
            }

//            if(sys.first == 1)
//            {
//                std::cout<<std::endl<<std::endl;
//                std::cout<<"delaycout "<<sys2.second->m_delayCounter<<std::endl;
//                std::cout<<"delay "<<sys2.second->m_delay<<std::endl;
//                //                std::cout<<"updating 1"<<std::endl;
//            }
            //            std::cout<<"system "<<sys2.first<<std::endl;
            sys2.second->m_delayCounter = 0;
            sys2.second->update();
        }

    }
}

bool SystemManager::attachComponent(System *sys, const ecsint cid)
{
    Component *c = getComponent(sys->entityId(),cid);
    assert(c);
    if(!c)
        return false;
    return sys->attachComponent(cid,c);
}

bool SystemManager::detachComponent(System *sys, const ecsint cid)
{
//    std::cout <<"detached "<<cid<<std::endl;
    return sys->detachComponent(cid);
}

Component *SystemManager::getComponent(const ecsint eid, const ecsint cid)
{
    return m_componentMap[eid][cid].get();
}

System *SystemManager::getSystem(const ecsint eid, const ecsint id)
{
    return m_systemMap[eid][id].get();
}



