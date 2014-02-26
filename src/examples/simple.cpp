#include <iostream>
#include <cassert>
#include "../ECS/ECS.h"
#include "../ECS/systemmanager.h"

#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../myecs/Systems/smovement.h"

#include <functional>
#include <chrono>


using namespace ECS;

int main()
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const ECS::ecsint MAX = 5;
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

    if(play == MAX)
        return MAX;


    ECS::SMovement *smo = m_sysFact.getMovementSystem(play,sysman);
    assert(smo);


//
//    ok &= sysman.attachComponent(smo,CENUM::CSPEED);
//    ok &= sysman.detachComponent(smo,CENUM::CINPUT);
//    ok &= sysman.attachComponent(smo,CENUM::CPOSITION);


    if(!ok)
    {
        return(101);
    }
//    smo->getPositionComponent()->setX(50);


    smo->setDelay(duration_cast<nanoseconds>(seconds(1)));


    unsigned long long i = 0;

    duration<double,std::nano> looptime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
    duration<double,std::nano> timetaken;
    while(timetaken < std::chrono::seconds(5))
    {



        int x = 0;


            looptime = end - loopstart;
            loopstart = end;
            end = high_resolution_clock::now();
            sysman.update(looptime);



        i++;
        timetaken = end - start;
    }
    std::cerr<<"Total Time::"<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl<<"Iterations::"<<i<<std::endl;
    std::cerr<<"SMovement iterations::"<<SMovement::counter<<std::endl;
    std::cerr<<"SBounds iterations::"<<SBounds::counter<<std::endl;
    std::flush(std::cerr);
    return 0;
}



