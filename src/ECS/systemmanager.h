#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "component.h"
#include "system.h"
#include "entities.h"
#include "ECS.h"
#include <chrono>
namespace ECS
{
class SystemManager
{

    typedef std::function<std::unique_ptr<ECS::Component> (ECS::ecsint,ECS::ecsint)> compFactoryFunction;
    typedef std::function<std::unique_ptr<ECS::System> (ECS::ecsint,ECS::ecsint)> sysFactoryFunction;


    typedef std::unique_ptr<Component> compUp;
    typedef std::unique_ptr<System> sysUp;

    typedef std::unordered_map<ecsint,compUp> compMapUP;
    typedef std::unordered_map<ecsint,sysUp> sysMapUP;
public:

    typedef std::unordered_map<ecsint,compMapUP> compMap;
    typedef std::unordered_map<ecsint,sysMapUP> sysMap;

    explicit SystemManager(const ECS::ecsint MAX, const compFactoryFunction &compFact, const sysFactoryFunction &sysFact);
    ~SystemManager();
    const ECS::ecsint addEntity(const ecsint &systems, const ecsint &component);

    using hilow = std::unordered_map<std::string,ECS::ecsint>;
    hilow bounds(ECS::ecsint num)
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

    template<class T1,class T2>
    bool  addToMap(const ecsint &bits, const ecsint &index, const T1 &factory,T2 &map)
    {
        hilow bnds = bounds(bits);

        bool success = false;
        for (int i = bnds.at("low");i<=bnds.at("high");)
        {

            if((i & bits) == i)
            {
                if((map[index][i] = factory(i,index)))
                    success = true;
            }
            i!=0 ? i*=2 : i++;
        }
        return success;
    }

    void update(const std::chrono::duration<double, std::nano> &time_span);
    void setSystemUpdate(bool update, ecsint sysid, ecsint eid);


    bool attachComponent(System *sys, const ecsint cid);

    bool detachComponent(System *sys, const ecsint cid);




    ECS::ecsint entityCount();
    Component *getComponent(const ecsint eid, const ecsint cid);
    System *getSystem(const ecsint eid, const ecsint id);


private:
    void addrefs(ECS::ecsint eid,System *sys)
    {
        sys->addRef(&m_componentMap[eid]);
    }
    std::unique_ptr<Entities>m_entities{};

    compMap m_componentMap;
    sysMap m_systemMap;

    compFactoryFunction m_compFact;
    sysFactoryFunction m_sysFact;
    const ecsint MAX;
};
}
#endif // SYSTEMMANAGER_H