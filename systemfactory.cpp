#include "systemfactory.h"
//#include "ECS/Systems/smovement.h"
//#include "ECS/Systems/sinput.h"
//#include "ECS/Systems/sposition.h"
#include "smovement.h"
//std::unique_ptr<ECS::System> systemFactory::operator()()
//{
//    return std::unique_ptr<ECS::System>(new ECS::SMovement());
//}


std::unique_ptr<ECS::System> systemFactory::operator()(ECS::ecsint type, std::string name)
{
    switch(type)
    {
//    case SMOVEMENT:
//        return std::unique_ptr<ECS::System>(new ECS::SMovement(name));
//    case SINPUT:
//        return std::unique_ptr<ECS::System>(new ECS::SInput(name));
    case SMOVEMENT:
        return std::unique_ptr<ECS::System>(new ECS::SMovement(name));
    default:
        return nullptr;
    }
}
