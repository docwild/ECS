#include <iostream>
#include <cassert>
#include "../ECS/ECS.h"
#include "../ECS/entitymanager.h"

#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../myecs/Systems/smovement.h"

#include <functional>
#include <chrono>
#include <random>


using namespace ECS;

int main()
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const ECS::ecsint MAX = 500;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    EntityManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;

    //    ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
    //    ok &= sysman.registerType(CENUM::CSPEED,"Position",sysman.compTypes());
    //    ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());

    if(!ok)
        return(100);
    ECS::ecsint ie=0;

    std::random_device rd;
    std::uniform_int_distribution<int> dist(3000, 10000);

    while( true )
    {
        if(ie == MAX-1)
            break;
        ie  = sysman.addEntity(SENUM::SMOVEMENT,
                               CENUM::CPOSITION|CENUM::CSPEED);

        ECS::SMovement *smo = m_sysFact.getMovementSystem(ie,sysman);
        assert(smo);

        //        ok &= sysman.attachComponent(smo,CENUM::CPOSITION);
        //        ok &= sysman.attachComponent(smo,CENUM::CSPEED);
        if(!ok)
        {
            return(101);
        }
        smo->setDelay(duration_cast<nanoseconds>(milliseconds(dist(rd))));
        //        smo->build(ie);
    }

    unsigned long long i = 0;

    duration<double,std::nano> looptime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
    duration<double,std::nano> timetaken;
    while(timetaken < std::chrono::seconds(5)/*i < 10000000*/)
    {



        int x = 0;

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


    //    std::cout << "SMOVEMENT called: "<<SMovement::called<<std::endl;
    std::flush(std::cout);
    std::cerr<<"Total Time::"<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl<<"Iterations::"<<i<<std::endl;
    std::cerr<<"SMovement iterations::"<<SMovement::counter<<std::endl;
    std::cerr<<"SBounds iterations::"<<SBounds::counter<<std::endl;
    std::cerr<<"Total entities = "<<sysman.entityCount()<<std::endl;

}

