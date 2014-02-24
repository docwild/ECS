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
    ecsint TOP{0};
    const std::vector<ecsint> &components() const;
    Entities(const ECS::ecsint MAX);

    template<class T>
    void setFlags(const ecsint &index, const ecsint &flags, T &vec)
    {
        vec[index] |= flags;
    }

    template<class T>
    void removeFlags(const ecsint &index, const ecsint &flags, T &vec)
    {
        vec[index] &= (~flags);
    }

    template<class T>
    void toggleFlags(const ecsint &flags, const ecsint &index,T &vec)
    {
        vec[index] ^= flags;
    }

    template<class T>
    const bool hasFlags(const ecsint &index, const T &vec) const
    {
        return vec[index]!=0;
    }

    template<class T>
    const bool hasFlags(const ecsint &index,const ecsint &flags, const T &vec) const
    {
        return ((vec[index] & flags));
    }

    const ecsint addEntity(const ecsint comp);
    const bool removeEntity(const ecsint id);
    const ecsint MAX;
    std::vector<ecsint> m_components{};
    std::vector<ecsint> m_systems{};
};
}
#endif // ENTITIES_H
