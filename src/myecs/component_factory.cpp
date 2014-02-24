#include "component_factory.h"
#include "cposition.h"
#include "cspeed.h"
std::unique_ptr<ECS::Component> CompFactory::operator() (const ECS::ecsint type) const
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
        return std::unique_ptr<ECS::Component>(new ECS::CPosition());
    case CSPEED:
        return std::unique_ptr<ECS::Component>(new ECS::CSpeed());
//    case CSPRITE:
//        return std::unique_ptr<ECS::Component>(new ECS::CSprite(name));
    default:
        return nullptr;
    }
}

ECS::CSpeed *CompFactory::getSpeedComponent(const ECS::ecsint eid, ECS::SystemManager &sysman)
{
    return dynamic_cast<ECS::CSpeed*>(sysman.getComponent(eid,CENUM::CSPEED));
}
