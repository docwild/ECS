#include "cposition.h"
using namespace ECS;
CPosition::CPosition(ECS::ecsint eid, ecsint cid):Component(eid,cid)
{
    m_name="Position";
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
