#include "cspeed.h"
using namespace ECS;
CSpeed::CSpeed(ECS::ecsint eid):Component(eid)
{
    m_name="Speed";
}

const float CSpeed::getX() const
{
    return x;
}

void CSpeed::setX(const float value)
{
    x = value;
}

const float CSpeed::getY() const
{
    return y;
}

void CSpeed::setY(const float value)
{
    y = value;
}
float CSpeed::getDx() const
{
    return dx;
}

void CSpeed::setDx(float value)
{
    dx = value;
}
float CSpeed::getDy() const
{
    return dy;
}

void CSpeed::setDy(float value)
{
    dy = value;
}


