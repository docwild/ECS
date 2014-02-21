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
#include <chrono>
//#include <SFML/Window/Event.hpp>
//#include <Aurora/Dispatch.hpp>
//class Entities;
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
    const ECS::ecsint addEntity(const ecsint &systems, const ecsint &component, const compFactoryFunction &cf, const sysFactoryFunction &sf);


    template<class T1,class T2,class T3>
    /**
     * @brief
     *  Add factory generated system or component to the relevant map.
     * @param bits
     *  Logical ORed list of components/systems
     * @param index
     *  Entity ID
     * @param mapType
     *  The proper typedef for the maptype
     * @param factory
     *  The factory funcion
     * @param map
     *  The map
     */
    bool  addToMap(const ecsint &bits, const ecsint &index, const T1 &mapType, const T2 &factory,T3 &map)
    {
        bool success = false;
        for (const auto &st: mapType)
        {

            if((st.first & bits) == st.first)
            {
//                mapUp[st.first] = factory(st.first,st.second,index);
                if(map[index][st.first] = factory(st.first,st.second,index))
                    success = true;
            }
        }
//        map[index] = std::move(mapUp);
        return success;
    }

    void update(const double time_span);


    /**
     * @brief
     *  Attaches a registered component to a system
     * @param sys
     *  The system object
     * @param cid
     *  The component ID
     * @return bool
     *  Returns false on failure
     */
    bool attachComponent(System *sys, const ecsint cid);

    /**
     * @brief
     *  Detaches an already attached component from a system
     * @param sys
     *  The system object
     * @param cid
     *  The component ID
     * @return bool
     *  False if there is no attached component by this ID
     */
    bool detachComponent(System *sys, const ecsint cid);


    template<class T1>
    /**
     * @brief
     *  Registers a type, component or system
     * @param id
     *  The ID of component/system
     * @param descriptive
     *  A descriptive name for the component/system
     * @param map
     *  The map to operate on
     * @return bool
     *  False on failure
     */
    bool registerType(const ECS::ecsint id, const std::string &descriptive, T1 &map)
    {

        const auto it = map.find(id);
        if(it == map.end())
        {
            map[id] = descriptive;
            return true;
        }
        return false;
    }

    Component *getComponent(const ecsint eid, const ecsint cid);
    System *getSystem(const ecsint eid, const ecsint id);
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
    std::unique_ptr<Entities>m_entities{};

    compMap m_componentMap;
    sysMap m_systemMap;
    const ecsint MAX;
};
}
#endif // SYSTEMMANAGER_H
