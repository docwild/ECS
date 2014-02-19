#ifndef POSITION_H
#define POSITION_H
#include "ECS/component.h"
#include <iostream>
namespace ECS
{
class CPosition : public Component
{
public:
    explicit CPosition(std::string name,ECS::ecsint eid);
    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);
    ~CPosition(){/*std::cout <<" pos destructor"<<std::endl;*/};
private:
    float x;
    float y;
};
}
#endif // POSITION_H
