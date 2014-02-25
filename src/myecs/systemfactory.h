#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H
#include <memory>
#include "../ECS/system.h"
#include "../ECS/ECS.h"
#include "smovement.h"
#include "sbounds.h"
#include "../ECS/systemmanager.h"
enum SENUM:ECS::ecsint
{

    SINPUT = 1 << 0,
    SPOSITION = 1 << 1,
    SMOVEMENT = 1 << 2,
    SACTIONS = 1 << 3,
    SBOUNDS = 1 << 4

};
class SystemFactory
{
public:
    std::unique_ptr<ECS::System> operator() (const ECS::ecsint type,const ECS::ecsint eid) const;
    ECS::SMovement *getMovementSystem(const ECS::ecsint eid,ECS::SystemManager &sysman);
    ECS::SBounds *getBoundsSystem(const ECS::ecsint eid,ECS::SystemManager &sysman);
};

#endif // SYSTEMFACTORY_H
