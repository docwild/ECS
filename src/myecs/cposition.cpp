#include "cposition.h"
using namespace ECS;
CPosition::CPosition():Component("Position")
{
//    std::cout<<"IN CPOSITION: name= "<<m_name<<std::endl;
}

const float CPosition::getX() const
{
    return x;
}

void CPosition::setX(const float value)
{
    x = value;
}

const float CPosition::getY() const
{
    return y;
}

void CPosition::setY(const float value)
{
    y = value;
}
