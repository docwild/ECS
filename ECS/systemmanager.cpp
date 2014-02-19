#include "systemmanager.h"
#include <iostream>
#include <cassert>
using namespace ECS;


SystemManager::SystemManager(const ecsint MAX):MAX(MAX)
{
m_entities.reset( new Entities(MAX));
}

SystemManager::~SystemManager()
{


}


void SystemManager::removeComponent(const ecsint &component, const ecsint &index)
{

    m_entities->removeComponent(component,index);
    removeComponentVector(index,component);

}


void SystemManager::removeComponentVector(const ecsint &index, const ecsint &component)
{

    for(auto &ct: m_compTypes)
    {
        if((component & ct.first) == ct.first)
            m_componentMap[ct.first][index] = nullptr;
    }

}

bool SystemManager::buildCompArrays()
{
    if(m_compTypes.empty())
        return false;
    for(auto &ct: m_compTypes)
    {
        m_componentMap[ct.first] =std::vector<compSp>(MAX);
    }
    return true;
}

bool SystemManager::buildSysArrays()
{
    if(m_sysTypes.empty())
        return false;
    for(const auto &st : m_sysTypes)
    {
        m_systemMap[st.first] = std::vector<sysSp>(MAX);
    }
    return true;
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





unsigned int SystemManager::addEntity(const ecsint &systems, const ecsint &component, compFactoryFunction cf, sysFactoryFunction sf)
{
    if(component == 0)
        return MAX;
    if(m_componentMap.empty())
        throw MAX;
    ecsint index = m_entities->addEntity(component);
    if(index == MAX)
        throw MAX;
    m_entities->setComponents(index,component);
    addToMap(component,index,m_compTypes,cf,m_componentMap);
    addToMap(systems,index,m_sysTypes,sf,m_systemMap);
    return index;
}

void SystemManager::update(bool inputFlag)
{

}


