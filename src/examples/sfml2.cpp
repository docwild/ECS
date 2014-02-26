//#include "config.h"
#include <iostream>
#include <chrono>
#include <cassert>
#include <random>
#include <SFML/Graphics.hpp>
#include "../ECS/ECS.h"
#include "../ECS/systemmanager.h"

#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../myecs/smovement.h"
using namespace std;
using namespace ECS;

int main(int argc, char* argv[])
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int SIZEX=800;
    const int SIZEY=600;
    const ECS::ecsint MAX = 2000;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    SystemManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;




    ECS::ecsint ie=0;

    std::random_device rd;
    std::uniform_int_distribution<int> ps_dist(0, 500);
    std::uniform_int_distribution<int> sz_dist(5, 5);
    std::uniform_int_distribution<int> ms_dist(5, 20);
    std::uniform_int_distribution<int> lt_dist(0, 1000);
    std::uniform_real_distribution<float> sp_dist(0.1, 5);
    std::vector<SDraw*> sdr_vec{};
    std::unordered_map<ECS::ecsint, SDraw*>sdr_map{};
    while( true )
    {
        if(ie == MAX-1)
            break;
        ie  = sysman.addEntity(SMOVEMENT|SDRAW|SBOUNDS,
                               CPOSITION|CSPEED|CSIZE|CBOUNDS);


        ECS::SMovement *smo = m_sysFact.getMovementSystem(ie,sysman);
        assert(smo);
        ECS::SDraw *sdr = m_sysFact.getDrawSystem(ie,sysman);
        assert(sdr);
        ECS::SBounds *sbo = m_sysFact.getBoundsSystem(ie,sysman);
        assert(sbo);

        CBounds *cb = sbo->cBounds();
        cb->setX(0);
        cb->setX1(SIZEX);
        cb->setY(0);
        cb->setY1(SIZEY);

        sdr->getSizeComponent()->setWidth(sz_dist(rd));
        sdr->getSizeComponent()->setHeight(sz_dist(rd));
        sdr_vec.push_back(sdr);
        sdr_map.emplace(ie,sdr);
        sdr->init(sdr_map,lt_dist(rd));
        sysman.chainSystem(smo,sdr,std::bind(&SDraw::update,sdr));
        sysman.chainSystem(sdr,sbo,std::bind(&SBounds::update,sbo));
        //    sbo->setDelay(duration_cast<nanoseconds>(milliseconds(1000)));
        smo->setDelay(duration_cast<nanoseconds>(milliseconds(10)));
        smo->getPositionComponent()->setX(ps_dist(rd));
        smo->getPositionComponent()->setY(ps_dist(rd));
        smo->getSpeedComponent()->setDx(sp_dist(rd));
        smo->getSpeedComponent()->setDy(sp_dist(rd));
        smo->getSpeedComponent()->setMx(ms_dist(rd));
        smo->getSpeedComponent()->setMy(ms_dist(rd));
        sdr->makeRect();
        //        smo->build(ie);
    }





    sf::RenderWindow App(sf::VideoMode(SIZEX, SIZEY), "myproject");


    //    sf::RectangleShape rectShape(sf::Vector2f(600,25));

    //    rectShape.setOutlineColor(sf::Color(0,0,0,255));
    //    rectShape.setOutlineThickness(2);

    duration<double,std::nano> looptime;
    duration<double,std::nano> sfmltime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
    sfmltime = duration_cast<nanoseconds>(seconds(0));
    duration<double,std::nano> timetaken;
    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();

        }

        looptime = end - loopstart;
        loopstart = end;
        end = high_resolution_clock::now();
        sysman.update(looptime);
        if(sfmltime > milliseconds(16))
        {
            App.clear();

            for(auto s:sdr_map)
            {
                App.draw(s.second->getRect());
            }
            App.display();
            sfmltime = duration_cast<nanoseconds>(seconds(0));
        }
        sfmltime+=looptime;

        //        rectShape.setPosition(smo->getPositionComponent()->getX(),smo->getPositionComponent()->getY());

    }
}


