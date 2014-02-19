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
    explicit System(std::string name,ECS::ecsint eid);
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){};
    virtual void update()=0;
    virtual void attachComponent(ecsint eid, Component *comp);
    std::string name() const;
    void setName(const std::string &name);

    std::unordered_map<ecsint, Component *> compMap() const;

    ECS::ecsint entityId() const;

protected:
    std::string m_name;
    unsigned int delay{0};
    std::unordered_map<ECS::ecsint, Component*> m_compMap;
    ECS::ecsint m_entityId;
};
}
#endif // SYSTEM_H
