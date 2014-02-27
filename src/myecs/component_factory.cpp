#include "component_factory.h"
#include "Components/cposition.h"
#include "Components/cspeed.h"
#include "Components/cinput.h"
#include "Components/cbounds.h"
#include "Components/caction.h"
#include "Components/csize.h"
std::unique_ptr<ECS::Component> CompFactory::operator() (const ECS::ecsint type,const ECS::ecsint eid) const
{
    switch(type)
    {
    case CACTIONS:
        return std::unique_ptr<ECS::Component>(new ECS::CAction(eid,CACTIONS));
    case CBOUNDS:
        return std::unique_ptr<ECS::Component>(new ECS::CBounds(eid,CBOUNDS));
    case CINPUT:
        return std::unique_ptr<ECS::Component>(new ECS::CInput(eid,CINPUT));
    case CPOSITION:
        return std::unique_ptr<ECS::Component>(new ECS::CPosition(eid,CPOSITION));
    case CSPEED:
        return std::unique_ptr<ECS::Component>(new ECS::CSpeed(eid,CSPEED));
    case CSIZE:
        return std::unique_ptr<ECS::Component>(new ECS::CSize(eid,CSIZE));
//    case CSPRITE:
//        return std::unique_ptr<ECS::Component>(new ECS::CSprite(name));
    default:
        return nullptr;
    }
}
