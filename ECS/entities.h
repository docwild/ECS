#ifndef ENTITIES_H
#define ENTITIES_H
#include <vector>
//#include <memory>
//#include "systemmanager.h"
//#include "component.h"
#include "ECS.h"
//class SystemManager;
//class compFactoryFunction;
//class sysFactoryFunction;
namespace ECS
{

class Entities
{
public:
    friend class SystemManager; // access to this class is through the manager only
    Entities() = delete;
    Entities(Entities const&) = delete; //no copying
    Entities& operator=(Entities const&) = delete; //no copying


private:
    const std::vector<ecsint> &components() const;
    Entities(const ECS::ecsint MAX);
    void setComponents(const ecsint &index, const ecsint &comp);
    void removeComponent(const ecsint &component, const ecsint &index);
    void toggleComponent(const ecsint &component, const ecsint &index);//not used but here for reference
    const bool hasComponents(const ecsint &index) const;
    const bool hasComponents(const ecsint &index,const ecsint &components) const;
    const ecsint addEntity(const ecsint comp);
    const bool removeEntity(const ecsint id);
    const ecsint MAX;
    std::vector<ecsint> m_components{};
};
}
#endif // ENTITIES_H
