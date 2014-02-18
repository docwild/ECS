#include "smovement.h"
#include "cspeed.h"
#include "cposition.h"
#include <cassert>
using namespace ECS;
SMovement::SMovement(std::string name):System(name)
{
}

void SMovement::update(const ecsint &index, const std::vector<Component *> &vec)
{
    std::cout << "In index["<<index<<"]."<<std::endl;

    ECS::CPosition *cpos = dynamic_cast<ECS::CPosition*>(vec[0]);
    ECS::CSpeed *cspeed = dynamic_cast<ECS::CSpeed*>(vec[1]);

    assert(cpos);
    std::cout <<cpos->name()<<" X: "<<cpos->getX()<<std::endl;


    if(cspeed)
    {
        cpos->setX(cpos->getX()+cspeed->getX());
        std::cout << cspeed->name()<<" X: "<<cspeed->getX()<<std::endl;
    }
    std::cout<<std::endl;
}
