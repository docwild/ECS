#include <iostream>
#include <cassert>
#include "ECS/ECS.h"
#include "ECS/systemmanager.h"

#include "component_factory.h"
#include "systemfactory.h"
#include "smovement.h"

#include <functional>
#include <ctime>
#include <chrono>

using namespace ECS;

int main()
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    const ECS::ecsint MAX = 5;
    compFactory m_compFact;

    systemFactory m_sysFact;
    SystemManager sysman(MAX);
    bool ok = true;

    ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
    ok &= sysman.registerType(CENUM::CSPEED,"Speed",sysman.compTypes());
    ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());

    if(!ok)
        return(100);


    const ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT,
                                              CENUM::CPOSITION|CENUM::CSPEED,
                                              m_compFact,m_sysFact);
    const ECS::ecsint nonplay = sysman.addEntity(SENUM::SMOVEMENT,
                                                 CENUM::CPOSITION,
                                                 m_compFact,m_sysFact);

    if(play == MAX || nonplay == MAX)
        return MAX;

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
    dynamic_cast<ECS::SMovement*>(smo)->getPositionComponent()->setX(50);
    dynamic_cast<ECS::SMovement*>(smo2)->getPositionComponent()->setX(500);
    dynamic_cast<ECS::SMovement*>(smo2)->setDelay(duration_cast<nanoseconds>(milliseconds(500)).count());
    dynamic_cast<ECS::SMovement*>(smo)->setDelay(duration_cast<nanoseconds>(milliseconds(2000)).count());

    //show attachments
    //    std::unordered_map<ecsint,Component*> req;// = smo->compMap();
    //    for(const auto i: std::vector<System*>{smo,smo2})
    //    {
    //        req = i->compMap();
    //        std::cout <<i->name()<<" System attachments for entity: "<<i->entityId()<<std::endl;
    //        for(const auto c: req)
    //        {
    //            std::cout<<"Attachment: "<<c.second->name()<<std::endl;
    //        }
    //    }
    typedef std::function<bool (System*,ECS::ecsint)> func;
    auto funcptr = std::bind(&SystemManager::detachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    auto funcptr2 = std::bind(&SystemManager::attachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    std::vector<func> vfunc{funcptr,funcptr2};

    //    double total_time = 0.0f;
    //    duration<double,std::milli> loop_time;
    //    loop_time.zero();
    unsigned long long i = 0;



    duration<double,std::nano> timetaken;
    duration<double,std::nano> looptime;

    auto end = high_resolution_clock::now();
    timetaken = end - start;
    auto loopstart = end;
    while(timetaken < std::chrono::seconds(10))
    {



        int x = 0;

        while (x++ < 5)
        {
            looptime = duration_cast<nanoseconds>(end - loopstart);
            loopstart = end;
            sysman.update(looptime.count());
            end = high_resolution_clock::now();
        }

        ok &= vfunc[i%2](smo,CENUM::CSPEED);
        if(!ok)
        {
            std::cout<<"Could not attach/detach"<<std::endl;
            break;
        }




        end = high_resolution_clock::now();
        timetaken = end - start;
        i++;
    }
    std::cout<<"I="<<i<<std::endl;
    std::cout<<"Time::"<<duration_cast<seconds>(timetaken).count()<<std::endl;
    return 0;
}

