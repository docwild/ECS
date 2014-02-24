#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <map>
#include "component.h"
#include "system.h"
//#include <string>
//#include "Components/cspeed.h"
//#include "Components/cposition.h"
//#include "Components/cinput.h"
//#include "Components/cactions.h"
//#include "Components/csprite.h"
//#include "Components/cbounds.h"
#include "entities.h"
//#include "Systems/smovement.h"
//#include "Systems/sinput.h"
//#include "Systems/sscenegraph.h"
#include "ECS.h"
#include <chrono>
//#include <SFML/Window/Event.hpp>
//#include <Aurora/Dispatch.hpp>
//class Entities;
namespace ECS
{
class SystemManager
{

//    typedef std::unordered_map<ECS::ecsint,std::string> registerMap;
    typedef std::function<std::unique_ptr<ECS::Component> (ECS::ecsint)> compFactoryFunction;
    typedef std::function<std::unique_ptr<ECS::System> (ECS::ecsint)> sysFactoryFunction;


    typedef std::unique_ptr<Component> compUp;
    typedef std::unique_ptr<System> sysUp;

    typedef std::unordered_map<ecsint,compUp> compMapUP;
    using MapBool = std::unordered_map<ecsint,bool>;
    using CompAttached = std::unordered_map<ecsint,MapBool>;
    typedef std::unordered_map<ecsint,sysUp> sysMapUP;
    typedef std::unordered_map<ecsint,compMapUP> compMap;
//    using mapEntSys = std::unordered_map<ecsint,ecsint>;
//    using typeVec = std::vector<ECS::ecsint>;
public:


//    typedef std::unordered_map<ecsint,sysMapUP> sysMap;

    explicit SystemManager(const ECS::ecsint MAX, const compFactoryFunction &compFact, const sysFactoryFunction &sysFact);
    ~SystemManager();
    const ECS::ecsint addEntity(const ecsint &systems=0, const ecsint &component=0);



    void update(const std::chrono::duration<double, std::nano> &time_span);
    void setSystemUpdate(bool update, ecsint sysid, ecsint eid);
    bool attachComponent(ECS::ecsint cid,ECS::ecsint eid);
//    bool addComponent(ECS::ecsint eid,ECS::ecsint cid)
//    {
//        auto it = m_compsMap.find(eid);
//        if(it == m_compsMap.end())
//        {

//        }
//        auto it2 = m_compsMap.at(eid).find(cid);
//        if(it2 == m_compsMap.at(eid).end())
//        {

//        }
//    }

    bool hasComponent(ECS::ecsint eid, ECS::ecsint cid)const
    {
        try
        {
            return m_compsAttached.at(eid).at(cid);
        }
        catch(std::out_of_range e)
        {
            return false;
        }
    }
    using hilow = std::map<std::string,ECS::ecsint>;
    hilow bounds(ECS::ecsint num);
    bool addComponents(ECS::ecsint components, ECS::ecsint eid)
    {
        if(components == 0)
            return true;
        auto it = m_compsMap.find(eid);
        if(it == m_compsMap.end())
        {
            m_compsMap.emplace(eid,compMapUP());
            m_compsAttached.emplace(eid,MapBool());

        }
        hilow b = bounds(components);
        bool success = true;
        for(ECS::ecsint i = b["low"]; i <= b["high"];)
        {
            if((i & components) == i)
            {
                try
                {
                    success &= registerType(m_compsMap.at(eid),m_compFact,i);

//                    m_compsAttached[eid][i] = success;
                    success &= attachComponent(i,eid);
                }
                catch (std::out_of_range e)
                {
                    success = false;
                }
            }
            i!=0 ? i*=2 : i++;
        }
        return success;
    }
    bool addSystems(ECS::ecsint systems, ECS::ecsint eid)
    {
        if(systems == 0)
            return true;
        hilow b = bounds(systems);
        bool success = true;
        for(ECS::ecsint i = b["low"]; i <= b["high"];)
        {
            if((i & systems) == i)
            {
                success &= registerType(m_systemsMap,m_sysFact,i);
                m_systemsMap[i]->addEntity(eid);
            }
            i!=0 ? i*=2 : i++;
        }
        return success;
    }




    ECS::ecsint entityCount();
    Component *getComponent(const ecsint eid, const ecsint cid);
    System *getSystem(const ecsint eid, const ecsint id);


private:

    template<class T1, class T2>
    bool registerType(T1 &map, T2 factory,ECS::ecsint id)
    {

        auto it = map.find(id);
        if(it == map.end())
        {

            map[id] = factory(id);
        }
        return true;
        //                m_systemsMap[i]->addEntity(eid);

    }
//    registerMap m_compTypes;
//    registerMap m_sysTypes;
//    typeVec m_svType;
//    typeVec m_comType;
    std::unique_ptr<Entities>m_entities{};

    //    compMap m_componentMap;
    //    sysMap m_systemMap;
    sysMapUP m_systemsMap{};
    compMap m_compsMap{};
    CompAttached m_compsAttached{};
//    mapEntSys m_entSys;

    compFactoryFunction m_compFact;
    sysFactoryFunction m_sysFact;
    const ecsint MAX;
};
}
#endif // SYSTEMMANAGER_H
