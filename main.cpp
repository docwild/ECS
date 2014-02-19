#include <iostream>
#include <cassert>
#include "ECS/ECS.h"
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
    const ECS::ecsint MAX = 50;
    compFactory m_compFact;

    systemFactory m_sysFact;
    SystemManager sysman(MAX);
    bool ok = true;

    ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
    ok &= sysman.registerType(CENUM::CSPEED,"Speed",sysman.compTypes());
    ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());

    if(!ok)
        return(100);


    ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT,
                                        CENUM::CPOSITION|CENUM::CSPEED,
                                        m_compFact,m_sysFact);
    ECS::ecsint nonplay = sysman.addEntity(SENUM::SMOVEMENT,
                                           CENUM::CPOSITION,
                                           m_compFact,m_sysFact);


    ECS::System *sys = sysman.getObject<ECS::System,ECS::SystemManager::sysMap>
            (SENUM::SMOVEMENT,play,sysman.systemMap());
    ECS::SMovement *smo = static_cast<ECS::SMovement*>(sys);
    assert(smo);

    sys = sysman.getObject<ECS::System,ECS::SystemManager::sysMap>
            (SENUM::SMOVEMENT,nonplay,sysman.systemMap());
    ECS::SMovement *smo2 = static_cast<ECS::SMovement*>(sys);
    assert(smo2);



    smo->attachComponent(CENUM::CSPEED,sysman.getObject<ECS::Component,ECS::SystemManager::compMap>
                         (CENUM::CSPEED,play,sysman.componentMap()));

    smo->attachComponent(CENUM::CPOSITION,sysman.getObject<ECS::Component,ECS::SystemManager::compMap>
                         (CENUM::CPOSITION,play,sysman.componentMap()));

    smo2->attachComponent(CENUM::CPOSITION,sysman.getObject<ECS::Component,ECS::SystemManager::compMap>
                          (CENUM::CPOSITION,nonplay,sysman.componentMap()));

    //show attachments
    std::unordered_map<ecsint,Component*> req;// = smo->compMap();
    for(auto i: std::vector<System*>{smo,smo2})
    {
        req = i->compMap();
        std::cout <<i->name()<<" System attachments for entity: "<<i->entityId()<<std::endl;
        for(auto c: req)
        {
            std::cout<<"Attachment: "<<c.second->name()<<std::endl;
        }
    }


    int x = 0;

    while (x++ < 15)
    {
        sysman.update();
        sleep(1);
    }
    return 0;
}

