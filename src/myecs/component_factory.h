#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <string>
#include <memory>
#include "../ECS/ECS.h"
#include "../ECS/component.h"
//#include "ECS/Components/cactions.h"
//#include "ECS/Components/cbounds.h"
//#include "ECS/Components/cinput.h"
//#include "ECS/Components/cposition.h"
//#include "ECS/Components/cspeed.h"
//#include "ECS/Components/csprite.h"
enum CENUM:ECS::ecsint
{
    CSPRITE = 1 << 0,
    CPOSITION = 1 << 1,
    CSPEED = 1 << 2,
    CINPUT = 1 << 3,
    CACTIONS = 1 << 4,
    CBOUNDS = 1 << 5,
    CSIZE = 1 << 6

};
class CompFactory
{
public:
    std::unique_ptr<ECS::Component> operator() (const ECS::ecsint type,const ECS::ecsint eid) const;
};
#endif // COMPONENT_FACTORY_H
