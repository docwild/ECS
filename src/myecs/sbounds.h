#ifndef SBOUNDS_H
#define SBOUNDS_H
#include "../ECS/system.h"
#include "cposition.h"
#include "cbounds.h"
#include "cspeed.h"
namespace ECS
{
class SBounds : public System
{
public:
    SBounds(ECS::ecsint eid);
    void update();
    bool attachComponent(ecsint eid,  Component * comp) override;
    bool detachComponent(ecsint cid) override;
    inline void setDelay(const std::chrono::duration<double, std::nano> delay){m_delay = delay;/*std::cout<<"Delay set: "<<delay.count()<<std::endl;*/}

    ECS::CPosition *getPositionComponent()const{return m_cPosition;}
    ECS::CBounds *cBounds() const{return m_cBounds;}

private:
    ECS::CPosition *m_cPosition;
    ECS::CBounds *m_cBounds;
    ECS::CSpeed *m_cSpeed;
};
}
#endif // SBOUNDS_H
