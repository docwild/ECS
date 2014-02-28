#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <unordered_map>
#include "component.h"
#include <chrono>
#include <memory>
#include <functional>
#include "ECS.h"
namespace ECS
{
class System
{
public:
    friend class EntityManager;
#ifdef UNITTEST
#endif
    typedef std::function<void()> listype;
    System() = delete;//no default
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){}
    inline const std::string &name() const;
    virtual void addListener(listype func);
    virtual bool attachComponent(ecsint cid, Component *comp)=0;
    virtual bool detachComponent(ecsint cid)=0;
    virtual void update()=0;
    virtual void setDelay( const std::chrono::duration<double, std::nano> delay)=0;
    const ECS::ecsint entityId() const;
    typedef std::unique_ptr<Component> compUp;
    typedef std::unordered_map<ecsint,compUp> CompMap;


    const CompMap * const cmap() const;
    void setCmap(CompMap *cmap);

protected:


    explicit System(ECS::ecsint eid,ECS::ecsint sid);
    void addRef(CompMap *cm)
    {
        m_cmap = cm;
//        for(auto &c:*m_cmap)
//        {
////            std::cout <<"c:"<<c.first<<std::endl;
//        }
    }

    std::string m_name{};
    std::chrono::duration<double, std::milli> m_delay{std::chrono::milliseconds(0)};
    std::chrono::duration<double, std::milli> m_delayCounter{std::chrono::milliseconds(0)};
    const CompMap *m_cmap;
    ECS::ecsint m_entityId{};
    ECS::ecsint m_systemId{};
    listype m_listenFunction{nullptr};
    bool m_update{true};
private:

    void setName(const std::string &name);
};
}
#endif // SYSTEM_H
