#include "component_factory.h"
#include "cposition.h"
#include "cspeed.h"
#include "cinput.h"
#include "cbounds.h"
#include "csize.h"
std::unique_ptr<ECS::Component> CompFactory::operator() (const ECS::ecsint type,const ECS::ecsint eid) const
{
    switch(type)
    {
//    case CACTIONS:
//        //        ra.reset(new ECS::CActions ());
//        return std::unique_ptr<ECS::Component>(new ECS::CActions(name));
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
