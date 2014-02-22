#include "component_factory.h"
#include "cposition.h"
#include "cspeed.h"
std::unique_ptr<ECS::Component> CompFactory::operator() (const ECS::ecsint type,const std::string &name,const ECS::ecsint eid) const
{
    switch(type)
    {
//    case CACTIONS:
//        //        ra.reset(new ECS::CActions ());
//        return std::unique_ptr<ECS::Component>(new ECS::CActions(name));
//    case CBOUNDS:
//        return std::unique_ptr<ECS::Component>(new ECS::CBounds(name));
//    case CINPUT:
//        return std::unique_ptr<ECS::Component>(new ECS::CInput(name));
    case CPOSITION:
        return std::unique_ptr<ECS::Component>(new ECS::CPosition(name,eid));
    case CSPEED:
        return std::unique_ptr<ECS::Component>(new ECS::CSpeed(name,eid));
//    case CSPRITE:
//        return std::unique_ptr<ECS::Component>(new ECS::CSprite(name));
    default:
        return nullptr;
    }
}
