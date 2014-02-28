#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H
#include <memory>
#include "../ECS/system.h"
#include "../ECS/ECS.h"
#ifdef DOSFMLFULL
#include "Systems/smovement-sfmlfull.h"
#include "Systems/sbounds-sfmlfull.h"
#include "Systems/sdraw-sfmlfull.h"
#else
#include "Systems/smovement.h"
#include "Systems/sbounds.h"
#endif
#ifdef DOSFML
#include "Systems/sdraw.h"
#endif
#include "../ECS/entitymanager.h"
enum SENUM:ECS::ecsint
{

    SINPUT = 1 << 0,
    SPOSITION = 1 << 1,
    SMOVEMENT = 1 << 2,
    SACTIONS = 1 << 3,
    SBOUNDS = 1 << 4,
    SDRAW = 1 << 5

};
class SystemFactory
{
public:
    std::unique_ptr<ECS::System> operator() (const ECS::ecsint type,const ECS::ecsint eid) const;
    ECS::SMovement *getMovementSystem(const ECS::ecsint eid,ECS::EntityManager &sysman);
    ECS::SBounds *getBoundsSystem(const ECS::ecsint eid,ECS::EntityManager &sysman);
#if defined(DOSFML) || defined(DOSFMLFULL)
    ECS::SDraw *getDrawSystem(const ECS::ecsint eid,ECS::EntityManager &sysman);
#endif
};

#endif // SYSTEMFACTORY_H
