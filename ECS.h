#ifndef ECS_H
#define ECS_H
#include <cstdint>
//#include "Components/cactions.h"
namespace ECS
{
typedef uint32_t ecsint;

const ecsint MAX = 50;
enum Layer
{
    Background,
    Intermediate,
    Foreground,
    LayerCount
};
//struct componentFactory
//{

//};
}
#endif // ECS_H
