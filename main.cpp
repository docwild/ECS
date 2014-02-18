#include <iostream>
#include <cassert>
//#include "ECS.h"
#include "ECS/systemmanager.h"

#include "component_factory.h"
#include "systemfactory.h"
#include "smovement.h"
#include "cposition.h"
#include "cspeed.h"

#include <unistd.h>

using namespace ECS;

int main()
{
    compFactory m_compFact;
    systemFactory m_sysFact;
    typedef std::unordered_map<ECS::ecsint,std::vector<std::unique_ptr<ECS::System>>> sysMap;
    typedef std::unordered_map<ECS::ecsint,std::vector<std::unique_ptr<ECS::Component>>> compMap;
    SystemManager sysman;
    bool ok = true;

    ok &= sysman.registerCompType(CENUM::CPOSITION,"Position");
    ok &= sysman.registerCompType(CENUM::CSPEED,"Speed");
    ok &= sysman.buildCompArrays();
    ok &= sysman.registerSysType(SENUM::SMOVEMENT,"Movement");
    ok &= sysman.buildSysArrays();
    if(!ok)
        return(100);
    ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT,
                                        CENUM::CPOSITION|CENUM::CSPEED,
                                        m_compFact,m_sysFact);
    ECS::ecsint nonplay = sysman.addEntity(SENUM::SMOVEMENT,
                                        CENUM::CPOSITION,
                                        m_compFact,m_sysFact);

    ECS::System *sys = sysman.getObject<ECS::System,sysMap>(SENUM::SMOVEMENT,play,sysman.systemMap());
    ECS::SMovement *smo = static_cast<ECS::SMovement*>(sys);
    assert(smo);

    ECS::System *sys2 = sysman.getObject<ECS::System,sysMap>(SENUM::SMOVEMENT,nonplay,sysman.systemMap());
    ECS::SMovement *smo2 = static_cast<ECS::SMovement*>(sys);
    assert(smo2);


    ECS::Component *comp = sysman.getObject<ECS::Component,compMap>(CENUM::CSPEED,play,sysman.componentMap());
    ECS::CSpeed *cspeed = dynamic_cast<ECS::CSpeed*>(comp);

    comp = sysman.getObject<ECS::Component,compMap>(CENUM::CPOSITION,play,sysman.componentMap());


    ECS::Component *comp2 = sysman.getObject<ECS::Component,compMap>(CENUM::CPOSITION,nonplay,sysman.componentMap());
//    ECS::CPosition *cposition = dynamic_cast<ECS::CPosition*>(comp);
//    std::cout <<"comp2 name= "<<comp2->name()<<std::endl;
    //    ECS::CPosition *cmo = static_cast<ECS::CPosition*>(comp);
    assert(cspeed && comp && comp2);
    //    cmo->setX(10);
    int x = 0;

    std::vector<Component*> cv{comp,cspeed};
    std::vector<Component*> cv2{comp2};
    cspeed->setX(cspeed->getX()+5);
    while (x++ < 5)
    {

        smo->update(play,cv);
        smo2->update(nonplay,cv2);

        sleep(1);
    }
    return 0;
}

