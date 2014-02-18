#ifndef ENTITIES_H
#define ENTITIES_H
#include <array>
#include <memory>
#include "component.h"
#include "../ECS.h"
namespace ECS
{

class Entities
{
public:
    Entities();
    Entities(Entities const&) = delete; //no copying
    Entities& operator=(Entities const&) = delete; //no copying
    const ecsint components(const ecsint index) const;
    void setComponents(const ecsint &index, const ecsint &comp);
    ecsint addEntity(const ecsint &comp);


    void removeComponent(const ecsint &component, const ecsint &index);
    void toggleComponent(const ecsint &component, const ecsint &index);//not used but here for reference
    const bool hasComponents(const ecsint &index) const;
    const bool hasComponents(const ecsint &index,const ecsint &components) const;
private:

    std::array<ecsint,MAX>m_components;
};
}
#endif // ENTITIES_H
