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
    explicit Component(const std::string &name,ECS::ecsint eid);
    Component(Component const&) = delete; //no copying
    Component& operator=(Component const&) = delete; //no copying
//    virtual void poly(){};//enable polymorphism for pointer downcasting
    virtual ~Component(){/*std::cout <<" comp destructor"<<std::endl;*/};
    std::string name() const;
    void setName(const std::string &name);

protected:
    std::string m_name{};

};
}
#endif // COMPONENT_H
