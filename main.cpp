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
#include <functional>

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


    ECS::System *smo = sysman.getSystem(play,SENUM::SMOVEMENT);
    assert(smo);

    ECS::System *smo2 = sysman.getSystem(nonplay,SENUM::SMOVEMENT);
    assert(smo2);

    ok &= sysman.attachComponent(smo,CENUM::CSPEED);
    ok &= sysman.attachComponent(smo,CENUM::CPOSITION);
//    ok &= sysman.attachComponent(smo,CENUM::CACTIONS);

    ok &= sysman.attachComponent(smo2,CENUM::CPOSITION);

    if(!ok)
    {
        return(101);
    }

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
    typedef std::function<bool (System*,ECS::ecsint)> func;
    auto funcptr = std::bind(&SystemManager::detachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    auto funcptr2 = std::bind(&SystemManager::attachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    std::vector<func> vfunc{funcptr,funcptr2};

    for(int i = 0; i < 3; i++)
    {
        int x = 0;

        while (x++ < 5)
        {
            sysman.update();
            sleep(1);
        }

        ok &= vfunc[i%2](smo,CENUM::CSPEED);
        if(!ok)
        {
            std::cout<<"Could not attach/detach"<<std::endl;
            break;
        }
    }


    return 0;
}

