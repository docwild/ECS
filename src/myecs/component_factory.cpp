#include "component_factory.h"
#include "cposition.h"
#include "cspeed.h"
#include "cinput.h"
std::unique_ptr<ECS::Component> CompFactory::operator() (const ECS::ecsint type,const ECS::ecsint eid) const
{
    switch(type)
    {
//    case CACTIONS:
//        //        ra.reset(new ECS::CActions ());
//        return std::unique_ptr<ECS::Component>(new ECS::CActions(name));
//    case CBOUNDS:
//        return std::unique_ptr<ECS::Component>(new ECS::CBounds(name));
    case CINPUT:
        return std::unique_ptr<ECS::Component>(new ECS::CInput(eid));
    case CPOSITION:
        return std::unique_ptr<ECS::Component>(new ECS::CPosition(eid));
    case CSPEED:
        return std::unique_ptr<ECS::Component>(new ECS::CSpeed(eid));
//    case CSPRITE:
//        return std::unique_ptr<ECS::Component>(new ECS::CSprite(name));
    default:
        return nullptr;
    }
}
