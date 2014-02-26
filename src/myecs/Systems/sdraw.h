#ifndef SDRAW_H
#define SDRAW_H
#include "../../ECS/system.h"
#include "../Components/cposition.h"
#include "../Components/csize.h"
#include <SFML/Graphics.hpp>
namespace ECS
{
class SDraw : public System
{
public:
    SDraw(ECS::ecsint eid, ecsint sid);
    void update();
    bool attachComponent(ecsint eid,  Component * comp) override;
    bool detachComponent(ecsint cid) override;
    inline void setDelay(const std::chrono::duration<double, std::nano> delay){m_delay = delay;/*std::cout<<"Delay set: "<<delay.count()<<std::endl;*/}
    static unsigned long long counter;
    void makeRect();
    ECS::CPosition *getPositionComponent()const{return m_cPosition;}
    ECS::CSize *getSizeComponent()const{return m_cSize;}
    const sf::Drawable &getRect()const {return *m_rectShape.get();}
    void init(std::unordered_map<ecsint,SDraw*> &drp,ecsint lt){m_drMap = &drp;m_lifetime=lt;}
private:
    ECS::CSize *m_cSize;
    ECS::CPosition *m_cPosition;
    std::unordered_map<ecsint,SDraw*> *m_drMap{nullptr};
    std::unique_ptr<sf::RectangleShape> m_rectShape{nullptr};
    sf::RenderWindow *m_win;
    ecsint m_lifetime{0};
};
}

#endif // SDRAW_H
