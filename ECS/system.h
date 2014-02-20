#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <unordered_map>
#include "component.h"

#include "ECS.h"
namespace ECS
{
class System
{
public:
    friend class SystemManager;

    System() = delete;//no default
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){}
    inline const std::string &name() const;


protected:
    virtual bool attachComponent(ecsint cid, Component *comp);
    virtual bool detachComponent(ecsint cid);
    virtual void update()=0;
    virtual void setDelay(const ecsint delay)=0;
    explicit System(const std::string &name,ECS::ecsint eid);
    const ECS::ecsint entityId() const;
    const std::unordered_map<ecsint, Component *> &compMap() const;
    std::string m_name{};
    double m_delay{0};
    double m_delayCounter{0};
    std::unordered_map<ECS::ecsint, Component*> m_compMap{};
    ECS::ecsint m_entityId{};
private:

    void setName(const std::string &name);
};
}
#endif // SYSTEM_H
