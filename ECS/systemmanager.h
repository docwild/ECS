#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>
#include <memory>
#include <unordered_map>
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
//#include <SFML/Window/Event.hpp>
//#include <Aurora/Dispatch.hpp>
namespace ECS
{
class SystemManager
{

    typedef std::unordered_map<ECS::ecsint,std::string> registerMap;
    typedef std::function<std::unique_ptr<ECS::Component> (ECS::ecsint,std::string,ECS::ecsint)> compFactoryFunction;
    typedef std::function<std::unique_ptr<ECS::System> (ECS::ecsint,std::string,ECS::ecsint)> sysFactoryFunction;

    typedef std::unique_ptr<Component> compUp;
    typedef std::unique_ptr<System> sysUp;

    typedef std::unordered_map<ecsint,compUp> compMapUP;
    typedef std::unordered_map<ecsint,sysUp> sysMapUP;
public:
    typedef std::unordered_map<ecsint,compMapUP> compMap;
    typedef std::unordered_map<ecsint,sysMapUP> sysMap;
    explicit SystemManager(const ECS::ecsint MAX);
    ~SystemManager();
    unsigned int addEntity(const ecsint &systems,const ecsint &component, compFactoryFunction cf, sysFactoryFunction sf);
    template<class T1,class T2,class T3,class T4>
    void  addToMap(const ecsint &bits, const ecsint &index, T1 &mapType, T2 factory,T3 &map, T4 mapVec)
    {
        for (const auto &st: mapType)
        {

            if((st.first & bits) == st.first)
            {
                mapVec[st.first] = factory(st.first,st.second,index);
            }
        }
        map[index] = std::move(mapVec);
    }
    void removeComponent(const ecsint &component,const ecsint &index);
    void removeComponentVector(const ecsint &index, const ecsint &component);
    void update();

    template<class T1>
    bool registerType(ECS::ecsint eid, std::string sid, T1 &map)
    {

        const auto it = map.find(eid);
        if(it == map.end())
        {
            map[eid] = sid;
            return true;
        }
        return false;
    }

    template<class T1,class T2>
    T1 *getObject(const ecsint id, const ecsint &index,T2 &map)
    {
        return map[index][id].get();
    }

    const sysMap &systemMap() const;
    sysMap &systemMap();

    const compMap &componentMap() const;
    compMap &componentMap();

    const registerMap &compTypes() const;
    registerMap &compTypes();

    const registerMap &sysTypes() const;
    registerMap &sysTypes();

private:
    registerMap m_compTypes;
    registerMap m_sysTypes;
    std::unique_ptr<Entities>m_entities;

    compMap m_componentMap;
    sysMap m_systemMap;
    const ecsint MAX;
};
}
#endif // SYSTEMMANAGER_H
