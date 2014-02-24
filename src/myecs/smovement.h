#ifndef SMOVEMENT_H
#define SMOVEMENT_H
#include "../ECS/system.h"

#include "../ECS/ECS.h"
#include "cspeed.h"
#include "cposition.h"
#include <memory>
namespace ECS
{
class SMovement : public System
{
public:
    explicit SMovement();
    void update();
    bool attachComponent(ecsint eid,  Component * comp) override;
    bool detachComponent(ecsint cid) override;
    inline void setDelay(const std::chrono::duration<double, std::nano> delay){m_delay = delay;/*std::cout<<"Delay set: "<<delay.count()<<std::endl;*/}
    bool addEntity(ecsint eid);
    static int called;

private:
    using SpeedUp = std::unique_ptr<ECS::CSpeed>;
    using SpeedMap = std::unordered_map<ECS::ecsint,SpeedUp>;
    using PositionUp = std::unique_ptr<ECS::CPosition>;
    using PositionMap = std::unordered_map<ECS::ecsint,PositionUp>;
    SpeedMap m_cSpeedMap;
    PositionMap m_cPositionMap;
    //    ECS::CSpeed *m_cSpeed;
    //    ECS::CPosition *m_cPosition;
};
}
#endif // SMOVEMENT_H

