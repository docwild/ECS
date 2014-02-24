#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "component.h"
#include <chrono>
#include <functional>
#include "ECS.h"
namespace ECS
{
class System
{
public:
    typedef std::unique_ptr<Component> compUp;
    typedef std::unique_ptr<System> sysUp;

    typedef std::unordered_map<ecsint,compUp> compMapUP;
//    using MapBool = std::unordered_map<ecsint,bool>;
//    using CompAttached = std::unordered_map<ecsint,MapBool>;
    typedef std::unordered_map<ecsint,sysUp> sysMapUP;
    typedef std::unordered_map<ecsint,compMapUP> CompMap;
    friend class SystemManager;
#ifdef UNITTEST
//    friend class MockSystem;
#endif
    typedef std::function<void()> listype;
    System() = delete;//no default
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){}
    inline const std::string &name() const;
    virtual void addListener(listype func);
    virtual bool attachComponent(ecsint cid, Component *comp);
    virtual bool detachComponent(ecsint cid);
    virtual void update()=0;
    virtual void setDelay( const std::chrono::duration<double, std::nano> delay)=0;
//    const ECS::ecsint entityId() const;
    using CompVec = std::vector<Component*>;
    const CompMap &compMap() const;
    void setCompMap(CompMap &cm);


protected:


    explicit System(const std::string &name);
    using entMap = std::unordered_map<ECS::ecsint,bool>;

    virtual bool addEntity(ECS::ecsint eid);
    bool hasSystem(ECS::ecsint eid);
    entMap m_entMap;


    CompMap *m_compMap{nullptr};

    std::string m_name{};
    std::chrono::duration<double, std::milli> m_delay{std::chrono::milliseconds(0)};
    std::chrono::duration<double, std::milli> m_delayCounter{std::chrono::milliseconds(0)};
//    std::unordered_map<ECS::ecsint, CompVec> m_compMap{};
//    ECS::ecsint m_entityId{};
    listype m_listenFunction{nullptr};
    bool m_update{true};
private:

    void setName(const std::string &name);
};
}
#endif // SYSTEM_H
