#ifndef SBOUNDS_H
#define SBOUNDS_H
#include "../../ECS/system.h"
#include "../Components/cposition.h"
#include "../Components/cbounds.h"
#include "../Components/cspeed.h"
#include "../Components/csize.h"
namespace ECS
{
class SBounds : public System
{
public:
    SBounds(ECS::ecsint eid, ecsint sid);
    void update();
    bool attachComponent(ecsint eid,  Component * comp) override;
    bool detachComponent(ecsint cid) override;
    inline void setDelay(const std::chrono::duration<double, std::nano> delay){m_delay = delay;/*std::cout<<"Delay set: "<<delay.count()<<std::endl;*/}

    ECS::CPosition *getPositionComponent()const{return m_cPosition;}
    ECS::CBounds *cBounds() const{return m_cBounds;}
    static unsigned long long counter;
private:
    ECS::CPosition *m_cPosition;
    ECS::CBounds *m_cBounds;
    ECS::CSpeed *m_cSpeed;
    ECS::CSize *m_cSize;
};
}
#endif // SBOUNDS_H
