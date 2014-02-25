//#include "config.h"
#include <iostream>
#include <chrono>
#include <cassert>
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
    const ECS::ecsint MAX = 5;
    CompFactory m_compFact;

    SystemFactory m_sysFact;
    SystemManager sysman(MAX,m_compFact,m_sysFact);
    bool ok = true;
    const ECS::ecsint rect = sysman.addEntity(SMOVEMENT|SDRAW|SBOUNDS,
                                              CPOSITION|CSPEED|CSIZE|CBOUNDS);


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

    sdr->getSizeComponent()->setWidth(100);
    sdr->getSizeComponent()->setHeight(50);
    sdr->makeRect();
    if(!ok)
    {
        return(101);
    }
    sysman.chainSystem(smo,sdr,std::bind(&SDraw::update,sdr));
    sysman.chainSystem(sdr,sbo,std::bind(&SBounds::update,sbo));
//    sbo->setDelay(duration_cast<nanoseconds>(milliseconds(1000)));
    smo->setDelay(duration_cast<nanoseconds>(milliseconds(10)));
    smo->getPositionComponent()->setX(100);
    smo->getPositionComponent()->setY(200);
    smo->getSpeedComponent()->setDx(0.5);

    sf::RenderWindow App(sf::VideoMode(SIZEX, SIZEY), "myproject");

//    sf::RectangleShape rectShape(sf::Vector2f(600,25));

//    rectShape.setOutlineColor(sf::Color(0,0,0,255));
//    rectShape.setOutlineThickness(2);

    duration<double,std::nano> looptime;
    auto end = high_resolution_clock::now();
    auto loopstart = end;
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
//        rectShape.setPosition(smo->getPositionComponent()->getX(),smo->getPositionComponent()->getY());
        App.clear();
        App.draw(sdr->getRect());
        App.display();
    }
}

