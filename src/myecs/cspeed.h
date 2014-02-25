#ifndef CSPEED_H
#define CSPEED_H
#include "../ECS/component.h"
#include <iostream>
namespace ECS
{
class CSpeed : public Component
{
public:
    explicit CSpeed(ECS::ecsint eid, ecsint cid);
    const float getX() const;
    void setX(const float value);

    const float getY() const;
    void setY(const float value);
    ~CSpeed(){/*std::cout <<" pos destructor"<<std::endl;*/};
    float getDx() const;
    void setDx(float value);

    float getDy() const;
    void setDy(float value);

private:
    float x{0};
    float y{0};
    float dx{0};
    float dy{0};
};
}
#endif // CSPEED_H
