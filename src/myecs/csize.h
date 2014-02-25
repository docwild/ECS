#ifndef CSIZE_H
#define CSIZE_H
#include "../ECS/component.h"
namespace ECS
{
class CSize : public Component
{
public:
    explicit CSize(ECS::ecsint eid, ecsint cid);
    float getWidth() const;
    void setWidth(float value);

    float getHeight() const;
    void setHeight(float value);

private:
    float width;
    float height;
};
}
#endif // CSIZE_H
