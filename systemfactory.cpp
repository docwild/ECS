#include "systemfactory.h"
//#include "ECS/Systems/smovement.h"
//#include "ECS/Systems/sinput.h"
//#include "ECS/Systems/sposition.h"
#include "smovement.h"
//std::unique_ptr<ECS::System> systemFactory::operator()()
//{
//    return std::unique_ptr<ECS::System>(new ECS::SMovement());
//}


std::unique_ptr<ECS::System> systemFactory::operator()(const ECS::ecsint type, const std::string &name,const ECS::ecsint eid) const
{
    switch(type)
    {
//    case SMOVEMENT:
//        return std::unique_ptr<ECS::System>(new ECS::SMovement(name));
//    case SINPUT:
//        return std::unique_ptr<ECS::System>(new ECS::SInput(name));
    case SMOVEMENT:
        return std::unique_ptr<ECS::System>(new ECS::SMovement(name,eid));
    default:
        return nullptr;
    }
}
