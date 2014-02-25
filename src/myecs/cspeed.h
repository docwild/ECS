#ifndef CSPEED_H
#define CSPEED_H
#include "../ECS/component.h"
#include <iostream>
namespace ECS
{
class CSpeed : public Component
{
public:
    explicit CSpeed(ECS::ecsint eid);
    const float getX() const;
    void setX(const float value);

    const float getY() const;
    void setY(const float value);
    ~CSpeed(){/*std::cout <<" pos destructor"<<std::endl;*/};
private:
    float x{0};
    float y{0};
};
}
#endif // CSPEED_H
