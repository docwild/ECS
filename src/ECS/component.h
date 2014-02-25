#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <string>
#include "ECS.h"
namespace ECS
{

class Component
{
public:
    friend class SystemManager;
    Component() = delete;
    Component(Component const&) = delete; //no copying
    Component& operator=(Component const&) = delete; //no copying
    virtual ~Component(){/*std::cout <<" comp destructor"<<std::endl;*/}
    std::string name() const;



protected:
    std::string m_name{};
    explicit Component(ECS::ecsint eid);
private:
    void setName(const std::string &name);

};
}
#endif // COMPONENT_H
