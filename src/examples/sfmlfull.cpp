//#include "config.h"
#include <iostream>
#include <chrono>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "../ECS/ECS.h"
#include "../ECS/systemmanager.h"

#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../myecs/Systems/smovement-sfmlfull.h"

#include "../myecs/Components/caction.h"
using namespace std;
using namespace ECS;

int main(int argc, char* argv[])
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int SIZEX=800;
    const int SIZEY=600;
    const ECS::ecsint MAX = 5;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    SystemManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;
    const ECS::ecsint rect = sysman.addEntity(SMOVEMENT|SDRAW|SBOUNDS,
                                              CPOSITION|CSPEED|CSIZE|CBOUNDS|CACTIONS);


    ECS::SMovement *smo = m_sysFact.getMovementSystem(rect,sysman);
    assert(smo);
    ECS::SDraw *sdr = m_sysFact.getDrawSystem(rect,sysman);
    assert(sdr);
    ECS::SBounds *sbo = m_sysFact.getBoundsSystem(rect,sysman);
    assert(sbo);

    CBounds *cb = sbo->cBounds();
    cb->setX(0);
    cb->setX1(SIZEX);
    cb->setY(0);
    cb->setY1(SIZEY);

    CAction *ca = static_cast<CAction*>(sysman.getComponent(rect,CACTIONS));
    assert(ca);
    ca->setActions("LEFT",false);
    ca->setActions("RIGHT",false);
    ca->setActions("UP",false);
    ca->setActions("DOWN",false);

    sdr->getSizeComponent()->setWidth(10);
    sdr->getSizeComponent()->setHeight(10);

    if(!ok)
    {
        return(101);
    }
    sysman.chainSystem(smo,sdr,std::bind(&SDraw::update,sdr));
    sysman.chainSystem(sdr,sbo,std::bind(&SBounds::update,sbo));
    //    sbo->setDelay(duration_cast<nanoseconds>(milliseconds(1000)));
    smo->setDelay(duration_cast<nanoseconds>(milliseconds(1000/60)));
    smo->getPositionComponent()->setX(100);
    smo->getPositionComponent()->setY(200);
    smo->getSpeedComponent()->setDx(0.0);
    smo->getSpeedComponent()->setMx(0.5);
    smo->getSpeedComponent()->setDy(0.0);
    smo->getSpeedComponent()->setMy(0.5);

    sf::RenderWindow App(sf::VideoMode(SIZEX, SIZEY), "myproject");
    std::unordered_map<ECS::ecsint, SDraw*>sdr_map{};
    sdr_map.emplace(rect,sdr);
    sdr->init(sdr_map);
    sdr->makeRect();
//    std::vector<SDraw*> sdr_vec{sdr};
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ca->setActions("LEFT",true);
        else
            ca->setActions("LEFT",false);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ca->setActions("RIGHT",true);
        else
            ca->setActions("RIGHT",false);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ca->setActions("UP",true);
        else
            ca->setActions("UP",false);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ca->setActions("DOWN",true);
        else
            ca->setActions("DOWN",false);
        looptime = end - loopstart;
        loopstart = end;
        end = high_resolution_clock::now();
        sysman.update(looptime);
        sfmltime+=looptime;
        //        rectShape.setPosition(smo->getPositionComponent()->getX(),smo->getPositionComponent()->getY());
        if(SDraw::draw_flag)
        {
            App.clear();
            for(auto s:sdr_map)
            {
                App.draw(s.second->getRect());
            }
            App.display();
            sfmltime = duration_cast<nanoseconds>(seconds(0));
            SDraw::draw_flag=false;
        }
    }
}

