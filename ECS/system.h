#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "component.h"
#include "../ECS.h"
namespace ECS
{
class System
{
public:
    explicit System(std::string name);
    System(System const&) = delete; //no copying
    System& operator=(System const&) = delete; //no copying
    virtual ~System(){};
    virtual void update(const ecsint &index, const std::vector<Component*> &vec)=0;
protected:
    std::string m_name;
};
}
#endif // SYSTEM_H
