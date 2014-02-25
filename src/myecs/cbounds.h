#ifndef CBOUNDS_H
#define CBOUNDS_H
#include "../ECS/component.h"

namespace ECS
{
class CBounds : public Component
{
public:
    CBounds(ecsint id);
    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getX1() const;
    void setX1(int value);

    int getY1() const;
    void setY1(int value);

private:
    int x;
    int y;
    int x1;
    int y1;
};
}
#endif // CBOUNDS_H
