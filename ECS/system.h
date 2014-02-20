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
    explicit System(const std::string &name,ECS::ecsint eid);
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){};
    virtual void update()=0;
    virtual bool attachComponent(ecsint cid, Component *comp);
    virtual bool detachComponent(ecsint cid);
    std::string name() const;
    void setName(const std::string &name);

    std::unordered_map<ecsint, Component *> compMap() const;

    const ECS::ecsint entityId() const;

protected:
    std::string m_name{};
    unsigned int delay{0};
    std::unordered_map<ECS::ecsint, Component*> m_compMap{};
    ECS::ecsint m_entityId{};
};
}
#endif // SYSTEM_H
