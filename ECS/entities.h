#ifndef ENTITIES_H
#define ENTITIES_H
#include <vector>
#include <memory>
#include "component.h"
#include "ECS.h"
namespace ECS
{

class Entities
{
public:
    Entities(const ECS::ecsint MAX);
    Entities(Entities const&) = delete; //no copying
    Entities& operator=(Entities const&) = delete; //no copying
    const std::vector<ecsint> &components() const;
    void setComponents(const ecsint &index, const ecsint &comp);
    ecsint addEntity(const ecsint &comp);


    void removeComponent(const ecsint &component, const ecsint &index);
    void toggleComponent(const ecsint &component, const ecsint &index);//not used but here for reference
    const bool hasComponents(const ecsint &index) const;
    const bool hasComponents(const ecsint &index,const ecsint &components) const;
private:
    const ecsint MAX;
    std::vector<ecsint> m_components;
};
}
#endif // ENTITIES_H
