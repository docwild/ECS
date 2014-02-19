#ifndef SMOVEMENT_H
#define SMOVEMENT_H
#include "ECS/system.h"
#include "cspeed.h"
#include "cposition.h"
namespace ECS
{
class SMovement : public System
{
public:
    explicit SMovement(std::string name,ECS::ecsint eid);
    void update();
    bool attachComponent(ecsint eid, Component *comp) override;
    bool detachComponent(ecsint cid) override;
private:
    ECS::CSpeed *m_cSpeed;
    ECS::CPosition *m_cPosition;
};
}
#endif // SMOVEMENT_H

