#ifndef CINPUT_H
#define CINPUT_H
#include "../ECS/component.h"
#include <vector>
#include <map>

namespace ECS
{
class CInput : public Component
{
public:
    CInput(ECS::ecsint eid, ecsint cid);
    ~CInput(){};



private:


};
}
#endif // CINPUT_H
