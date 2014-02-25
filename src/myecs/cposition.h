#ifndef POSITION_H
#define POSITION_H
#include "../ECS/component.h"
#include <iostream>
namespace ECS
{
class CPosition : public Component
{
public:
    explicit CPosition( ECS::ecsint eid);
    const float getX() const;
    void setX(const float value);

    const float getY() const;
    void setY(const float value);
    ~CPosition(){/*std::cout <<" pos destructor"<<std::endl;*/};
private:
    float x{0};
    float y{0};
};
}
#endif // POSITION_H
