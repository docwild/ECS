#include "component_factory.h"
#include "cposition.h"
#include "cspeed.h"
std::unique_ptr<ECS::Component> compFactory::operator() (ECS::ecsint type,std::string name)
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
        return std::unique_ptr<ECS::Component>(new ECS::CPosition(name));
    case CSPEED:
        return std::unique_ptr<ECS::Component>(new ECS::CSpeed(name));
//    case CSPRITE:
//        return std::unique_ptr<ECS::Component>(new ECS::CSprite(name));
    default:
        return nullptr;
    }
}
