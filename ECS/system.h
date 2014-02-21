#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
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
    friend class SystemManager;

    typedef std::function<void()> listype;
    System() = delete;//no default
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){}
    inline const std::string &name() const;
    virtual void addListener(listype func);

protected:
    virtual bool attachComponent(ecsint cid, Component *comp);
    virtual bool detachComponent(ecsint cid);
    virtual void update()=0;
    virtual void setDelay( const std::chrono::duration<double, std::nano> delay)=0;

    explicit System(const std::string &name,ECS::ecsint eid);
    const ECS::ecsint entityId() const;
    const std::unordered_map<ecsint, Component *> &compMap() const;
    std::string m_name{};
    std::chrono::duration<double, std::milli> m_delay{std::chrono::milliseconds(0)};
    std::chrono::duration<double, std::milli> m_delayCounter{std::chrono::milliseconds(0)};
    std::unordered_map<ECS::ecsint, Component*> m_compMap{};
    ECS::ecsint m_entityId{};
    listype m_listenFunction{nullptr};
    bool m_update{true};
private:

    void setName(const std::string &name);
};
}
#endif // SYSTEM_H
