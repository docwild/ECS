#ifndef CSPEED_H
#define CSPEED_H
#include "ECS/component.h"
#include <iostream>
namespace ECS
{
class CSpeed : public Component
{
public:
    explicit CSpeed(std::string name,ECS::ecsint eid);
    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);
    ~CSpeed(){/*std::cout <<" pos destructor"<<std::endl;*/};
private:
    float x;
    float y;
};
}
#endif // CSPEED_H
