#include <iostream>
#include <cassert>
#include "../ECS/ECS.h"
#include "../ECS/systemmanager.h"

#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../myecs/smovement.h"

#include <functional>
#include <chrono>


using namespace ECS;

int main()
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const ECS::ecsint MAX = 2;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    SystemManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;

//    ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
//    ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());

    if(!ok)
        return(100);


    const ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT,
                                              CENUM::CPOSITION|CENUM::CSPEED);
    const ECS::ecsint nonplay = sysman.addEntity();


    sysman.attachComponent(CENUM::CPOSITION,nonplay);
    assert(sysman.hasComponent(nonplay,CENUM::CPOSITION));
    assert(!sysman.hasComponent(nonplay,CENUM::CSPEED));
    assert(sysman.hasComponent(play,CENUM::CPOSITION));
    assert(sysman.hasComponent(play,CENUM::CSPEED));
    if(play > MAX)
        return MAX;


    ECS::SMovement *smo = m_sysFact.getMovementSystem(play,sysman);
    assert(smo);

    ECS::SMovement *smo2 = m_sysFact.getMovementSystem(nonplay,sysman);
    assert(!smo2);


//    ok &= sysman.attachComponent(smo,CENUM::CPOSITION);


    if(!ok)
    {
        return(101);
    }
    auto sp = m_compFact.getSpeedComponent(play,sysman);
    assert(sp);


    smo->setDelay(duration_cast<nanoseconds>(seconds(0)));


    unsigned long long i = 0;

    duration<double,std::nano> looptime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
    duration<double,std::nano> timetaken;
    while(/*timetaken < std::chrono::seconds(5)*/i < 10000)
    {



//        int x = 0;

//        while (x++ < 5)
//        {
            looptime = end - loopstart;
            loopstart = end;
            end = high_resolution_clock::now();
            sysman.update(looptime);
//        }


        i++;
        timetaken = end - start;
    }
    std::cout << "SMOVEMENT called: "<<SMovement::called<<std::endl;
    std::flush(std::cout);
    std::cerr<<"Total Time::"<<i<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl;
    std::cerr<<"Total entities = "<<sysman.entityCount()<<std::endl;
    return 0;
}



