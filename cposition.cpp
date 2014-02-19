#include "cposition.h"
using namespace ECS;
CPosition::CPosition(std::string name,ECS::ecsint eid):Component(name,eid)
{
//    std::cout<<"IN CPOSITION: name= "<<m_name<<std::endl;
}

float CPosition::getX() const
{
    return x;
}

void CPosition::setX(float value)
{
    x = value;
}

float CPosition::getY() const
{
    return y;
}

void CPosition::setY(float value)
{
    y = value;
}
