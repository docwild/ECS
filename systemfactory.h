#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H
#include <memory>
#include "ECS/system.h"
#include "ECS/ECS.h"
enum SENUM:ECS::ecsint
{
    SMOVEMENT = 1 << 0,
    SPOSITION = 1 << 1,
    SINPUT = 1 << 2,
    SACTIONS = 1 << 3,
    SBOUNDS = 1 << 4

};
class systemFactory
{
public:
    std::unique_ptr<ECS::System> operator() (ECS::ecsint type,std::string name);
};

#endif // SYSTEMFACTORY_H
