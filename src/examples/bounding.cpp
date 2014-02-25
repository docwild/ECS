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

    const ECS::ecsint MAX = 5;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    SystemManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;

//    ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
//    ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());

    if(!ok)
        return(100);


    const ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT|SENUM::SBOUNDS,
                                              CENUM::CPOSITION|CENUM::CSPEED);

    if(play == MAX)
        return MAX;


    ECS::SMovement *smo = m_sysFact.getMovementSystem(play,sysman);
    assert(smo);
    ECS::SBounds *sbo = m_sysFact.getBoundsSystem(play,sysman);
    assert(sbo);

//
    ok &= sysman.attachComponent(sbo,CENUM::CBOUNDS);
    ok &= sysman.detachSystem(play,SENUM::SBOUNDS);
//    ok &= sysman.detachComponent(smo,CENUM::CINPUT);
//    ok &= sysman.attachComponent(smo,CENUM::CPOSITION);


    if(!ok)
    {
        return(101);
    }
//    smo->getPositionComponent()->setX(50);


    smo->setDelay(duration_cast<nanoseconds>(milliseconds(500)));

    smo->addListener(std::bind(&SBounds::update,sbo));//chain updates, dont forget to disable auto updating for the chained system

    CBounds *cb = sbo->cBounds();
    cb->setX(0);
    cb->setX1(25);
    cb->setY(0);
    cb->setY(15);
    unsigned long long i = 0;

    duration<double,std::nano> looptime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
    duration<double,std::nano> timetaken;
    while(timetaken < std::chrono::seconds(15))
    {



        int x = 0;


            looptime = end - loopstart;
            loopstart = end;
            end = high_resolution_clock::now();
            sysman.update(looptime);



        i++;
        timetaken = end - start;
    }
    std::cerr<<"Total Time::"<<i<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl;
    std::flush(std::cerr);
    return 0;
}




