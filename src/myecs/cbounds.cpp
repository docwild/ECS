#include "cbounds.h"
using namespace ECS;
CBounds::CBounds(ecsint id):Component(id)
{
}
int CBounds::getX() const
{
    return x;
}

void CBounds::setX(int value)
{
    x = value;
}
int CBounds::getY() const
{
    return y;
}

void CBounds::setY(int value)
{
    y = value;
}
int CBounds::getX1() const
{
    return x1;
}

void CBounds::setX1(int value)
{
    x1 = value;
}
int CBounds::getY1() const
{
    return y1;
}

void CBounds::setY1(int value)
{
    y1 = value;
}




