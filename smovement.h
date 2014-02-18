#ifndef SMOVEMENT_H
#define SMOVEMENT_H
#include "ECS/system.h"
namespace ECS
{
class SMovement : public System
{
public:
    explicit SMovement(std::string name);
    void update(const ecsint &index, const std::vector<Component*> &vec);
};
}
#endif // SMOVEMENT_H
