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
#include "ECS/listener.h"

using namespace ECS;
class MyListener:public Listener
{
public:
    MyListener():Listener()
    {

    }
    void listen()
    {
        std::cout<<"listening 1"<<std::endl<<m_listenMessage<<std::endl;
    }
    std::string listenMessage() const
    {
    return m_listenMessage;
    }

    void setListenMessage(const std::string &listenMessage)
    {
    m_listenMessage = listenMessage;
    }

private:
    std::string m_listenMessage;
};
class MyListener2:public Listener
{
public:
    MyListener2():Listener()
    {

    }
    void listen()
    {
        std::cout<<"listening 2"<<std::endl<<m_number<<std::endl;
    }
    int number() const
    {
    return m_number;
    }

    void setNumber(const int &listenMessage)
    {
    m_number = listenMessage;
    }

private:
    int m_number;
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
    //    ok &= sysman.attachComponent(smo,CENUM::CACTIONS);

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
    dynamic_cast<ECS::SMovement*>(smo)->setDelay(duration_cast<nanoseconds>(milliseconds(200)));
    dynamic_cast<ECS::SMovement*>(smo3)->setDelay(duration_cast<nanoseconds>(milliseconds(800)));

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


    MyListener lis;
    MyListener2 lis2;
    lis.setListenMessage("THIS IS MY MESSAGE");
    lis2.setNumber(55);
//    typedef std::function<void()> listype;
//    System::listype lisfunc;
    auto lisptr = std::bind(&Listener::listen, &lis);
    auto lisptr2 = std::bind(&Listener::listen, &lis2);
    smo->addListener(lisptr);
    smo2->addListener(lisptr2);
    smo3->addListener([]{std::cout<<"lambda listener"<<std::endl;});
    //    double total_time = 0.0f;
    //    duration<double,std::milli> loop_time;
    //    loop_time.zero();
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
    while(/*timetaken < std::chrono::seconds(5)*/i < 100000)
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
//        if(high_resolution_clock::now() > timerfuture)
//        {
//            std::cerr<<"Time::"<<i<<"::"<<duration_cast<seconds>(timetaken).count()<<std::endl;
//            timerfuture = high_resolution_clock::now() + seconds(1);
//        }
    }
    std::cerr<<"Total Time::"<<i<<"::"<<duration_cast<seconds>(timetaken).count()<<" seconds"<<std::endl;
    std::flush(std::cerr);
    return 0;
}



