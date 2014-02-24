#ifndef SMOVEMENT_H
#define SMOVEMENT_H
#include "../ECS/system.h"

#include "../ECS/ECS.h"
#include "cspeed.h"
#include "cposition.h"
#include "component_factory.h"
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
    static unsigned long long called;
    void build(ECS::ecsint eid)
    {
        auto &comps = m_compMap->at(eid);
        try
        {
            m_cSpeedMap.emplace(eid,dynamic_cast<ECS::CSpeed*>(comps.at(CENUM::CSPEED).get()));
        }
        catch(std::out_of_range e)
        {

        }
        try
        {
            m_cPositionMap.emplace(eid,dynamic_cast<ECS::CPosition*>(comps.at(CENUM::CPOSITION).get()));
        }
        catch(std::out_of_range e)
        {

        }

    }

private:
    using SpeedRp = ECS::CSpeed*;
    using SpeedMap = std::unordered_map<ECS::ecsint,SpeedRp>;
    using PositionRp = ECS::CPosition*;
    using PositionMap = std::unordered_map<ECS::ecsint,PositionRp>;
    SpeedMap m_cSpeedMap;
    PositionMap m_cPositionMap;
    //    ECS::CSpeed *m_cSpeed;
    //    ECS::CPosition *m_cPosition;
};
}
#endif // SMOVEMENT_H

