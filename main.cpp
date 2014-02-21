#include <iostream>
#include <cassert>
#include "ECS/ECS.h"
#include "ECS/systemmanager.h"

#include "component_factory.h"
#include "systemfactory.h"
#include "smovement.h"

#include <functional>
#include <chrono>


using namespace ECS;

class MyListener
{
public:
    MyListener()
    {

    }
    System::listype operator()(int number)
    {
        m_number = number;
        return std::bind(&MyListener::listen, this);
    }
    System::listype operator()(std::string message)
    {
        m_listenMessage = message;
        return std::bind(&MyListener::listen2, this);
    }
    void listen()
    {
        std::cout<<"listening 1"<<std::endl<<m_number<<std::endl;
    }
    void listen2()
    {
        std::cout<<"listening 2"<<std::endl<<m_listenMessage<<std::endl;
    }

private:
    int m_number{0};
    std::string m_listenMessage;
};
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
    const ECS::ecsint extra = sysman.addEntity(SENUM::SMOVEMENT,
                                                 CENUM::CPOSITION|CENUM::CSPEED,
                                                 m_compFact,m_sysFact);

    if(play == MAX || nonplay == MAX || extra == MAX)
        return MAX;

    ECS::System *smo = sysman.getSystem(play,SENUM::SMOVEMENT);
    assert(smo);

    ECS::System *smo2 = sysman.getSystem(nonplay,SENUM::SMOVEMENT);
    assert(smo2);

    ECS::System *smo3 = sysman.getSystem(extra,SENUM::SMOVEMENT);
    assert(smo3);

    ok &= sysman.attachComponent(smo,CENUM::CSPEED);
    ok &= sysman.attachComponent(smo,CENUM::CPOSITION);

    ok &= sysman.attachComponent(smo2,CENUM::CPOSITION);

    ok &= sysman.attachComponent(smo3,CENUM::CSPEED);
    ok &= sysman.attachComponent(smo3,CENUM::CPOSITION);

    if(!ok)
    {
        return(101);
    }
    dynamic_cast<ECS::SMovement*>(smo)->getPositionComponent()->setX(50);
    dynamic_cast<ECS::SMovement*>(smo2)->getPositionComponent()->setX(5);


    dynamic_cast<ECS::SMovement*>(smo2)->setDelay(duration_cast<nanoseconds>(seconds(1)));
    dynamic_cast<ECS::SMovement*>(smo)->setDelay(duration_cast<nanoseconds>(milliseconds(500)));
    dynamic_cast<ECS::SMovement*>(smo3)->setDelay(duration_cast<nanoseconds>(milliseconds(1800)));

    typedef std::function<bool (System*,ECS::ecsint)> func;
    auto funcptr = std::bind(&SystemManager::detachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    auto funcptr2 = std::bind(&SystemManager::attachComponent, &sysman, std::placeholders::_1, std::placeholders::_2);
    std::vector<func> vfunc{funcptr,funcptr2};


    MyListener lis;
    MyListener lis2;

    smo->addListener(lis("THIS IS MY MESSAGE"));
    smo2->addListener(lis2(61));
    smo3->addListener([]{std::cout<<"lambda listener"<<std::endl;});

    unsigned long long i = 0;



    duration<double,std::nano> timetaken;
    duration<double,std::nano> looptime;
    duration<double,std::nano> timerdur;

    auto end = high_resolution_clock::now();
    timetaken = end - start;
    timerdur = end - start;
    auto loopstart = end;
    auto timer = end;
    auto timerfuture = high_resolution_clock::now() + seconds(1);
    while(/*timetaken < std::chrono::seconds(5)*/i < 1000000)
    {



        int x = 0;

        while (x++ < 5)
        {
            looptime = end - loopstart;
            loopstart = end;
            sysman.update(looptime);
            end = high_resolution_clock::now();
        }

//        ok &= vfunc[i%2](smo,CENUM::CSPEED);
        if(!ok)
        {
            std::cout<<"Could not attach/detach"<<std::endl;
            break;
        }




        end = high_resolution_clock::now();
        timetaken = end - start;
        i++;
    }
    std::cerr<<"Total Time::"<<i<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl;
    std::flush(std::cerr);
    return 0;
}



