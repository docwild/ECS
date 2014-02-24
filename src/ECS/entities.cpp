#include "entities.h"
#include "component.h"
#include <iostream>
using namespace ECS;
//ecsint Entities::TOP = 0;
Entities::Entities(const ecsint MAX):MAX(MAX),m_components(MAX),m_systems(MAX)
{

}



const std::vector<ecsint> &Entities::components() const
{
    return m_components;
}

//void Entities::setComponents(const ecsint &index, const ecsint &comp)
//{
//    m_components[index] |= comp;
//}
//void Entities::removeComponent(const ecsint &component, const ecsint &index)
//{
//    m_components[index] &= (~component);
//}

//void Entities::toggleComponent(const ecsint &component, const ecsint &index)
//{
//    m_components[index] ^= component;
//}
//const bool Entities::hasComponents(const ecsint &index,const ecsint &components) const
//{
//    return ((m_components[index] & components) == components);
//}

//const bool Entities::hasComponents(const ecsint &index) const
//{
//    return m_components[index]!=0;
//}

const ecsint Entities::addEntity(const ecsint comp)
{
    ecsint index = 0;
//    if(TOP==MAX)
//        return MAX+1;



    return TOP++;

}

const bool Entities::removeEntity(const ecsint id)
{
    if (id < m_components.size())
    {
        m_components[id] = 0;
        return true;
    }
    return false;
}




