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
    steady_clock::time_point t_start = steady_clock::now();
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
    dynamic_cast<ECS::SMovement*>(smo)->setDelay(1000);

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
    time_t timer;
    double total_time = 0.0f;
    double loop_time = 0.f;
    unsigned long long i = 0;


    steady_clock::time_point t1 = steady_clock::now();
    while(total_time < 1000*60*5)
    {

        int x = 0;

        while (x++ < 3)
        {
            sysman.update(loop_time);
            //            sleep(1);
        }

        ok &= vfunc[i%2](smo,CENUM::CSPEED);
        if(!ok)
        {
            std::cout<<"Could not attach/detach"<<std::endl;
            break;
        }
        steady_clock::time_point t2 = steady_clock::now();

        duration<double,std::milli> time_span = duration_cast<duration<double,std::milli>>(t2 - t1);

        loop_time = time_span.count();
        total_time += time_span.count();
        t1 = t2;
        i++;
//        std::cout <<"Time: " << total_time <<std::endl;
    }
    std::cout<<"I="<<i<<std::endl;
    steady_clock::time_point t_end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    std::cout<<"Time::"<<time_span.count()<<std::endl;
    return 0;
}

