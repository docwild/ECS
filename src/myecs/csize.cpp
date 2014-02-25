#include "csize.h"
using namespace ECS;
ECS::CSize::CSize(ECS::ecsint eid, ECS::ecsint cid):Component(eid,cid)
{

}
float CSize::getWidth() const
{
    return width;
}

void CSize::setWidth(float value)
{
    width = value;
}
float CSize::getHeight() const
{
    return height;
}

void CSize::setHeight(float value)
{
    height = value;
}


