#ifndef SMOVEMENT_H
#define SMOVEMENT_H
#include "../../ECS/system.h"
#include "../Components/cspeed.h"
#include "../Components/cposition.h"

namespace ECS
{
class SMovement : public System
{
public:
    explicit SMovement(ECS::ecsint eid, ecsint sid);
    void update();
    bool attachComponent(ecsint eid,  Component * comp) override;
    bool detachComponent(ecsint cid) override;
    inline void setDelay(const std::chrono::duration<double, std::nano> delay){m_delay = delay;/*std::cout<<"Delay set: "<<delay.count()<<std::endl;*/}

    static unsigned long long counter;
    ECS::CPosition *getPositionComponent()const{return m_cPosition;}


    ECS::CSpeed *getSpeedComponent() const{return m_cSpeed;}

private:
    ECS::CSpeed *m_cSpeed;
    ECS::CPosition *m_cPosition;
};
}
#endif // SMOVEMENT_H

