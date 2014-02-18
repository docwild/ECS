#include "cspeed.h"
using namespace ECS;
CSpeed::CSpeed(std::string name):Component(name)
{
//    std::cout<<"IN CSpeed: name= "<<m_name<<std::endl;
}

float CSpeed::getX() const
{
    return x;
}

void CSpeed::setX(float value)
{
    x = value;
}

float CSpeed::getY() const
{
    return y;
}

void CSpeed::setY(float value)
{
    y = value;
}
