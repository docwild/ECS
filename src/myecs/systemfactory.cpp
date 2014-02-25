#include "systemfactory.h"
//#include "ECS/Systems/smovement.h"
//#include "ECS/Systems/sinput.h"
//#include "ECS/Systems/sposition.h"

//std::unique_ptr<ECS::System> systemFactory::operator()()
//{
//    return std::unique_ptr<ECS::System>(new ECS::SMovement());
//}


std::unique_ptr<ECS::System> SystemFactory::operator()(const ECS::ecsint type,const ECS::ecsint eid) const
{
    switch(type)
    {
//    case SMOVEMENT:
//        return std::unique_ptr<ECS::System>(new ECS::SMovement(name));
//    case SINPUT:
//        return std::unique_ptr<ECS::System>(new ECS::SInput(name));
    case SMOVEMENT:
        return std::unique_ptr<ECS::System>(new ECS::SMovement(eid));
    case SBOUNDS:
        return std::unique_ptr<ECS::System>(new ECS::SBounds(eid));
    default:
        return nullptr;
    }
}

ECS::SMovement *SystemFactory::getMovementSystem(const ECS::ecsint eid, ECS::SystemManager &sysman)
{
    return dynamic_cast<ECS::SMovement*>(sysman.getSystem(eid,SENUM::SMOVEMENT));
}

ECS::SBounds *SystemFactory::getBoundsSystem(const ECS::ecsint eid, ECS::SystemManager &sysman)
{
    return dynamic_cast<ECS::SBounds*>(sysman.getSystem(eid,SENUM::SBOUNDS));
}
