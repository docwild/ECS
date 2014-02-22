#ifndef MOCKS_H
#define MOCKS_H
#include "gmock/gmock.h"

#include <chrono>
#include "../ECS/ECS.h"
#include "../ECS/system.cpp"
#include "../ECS/component.cpp"
class MockSystem : public ECS::System {

 public:
    MockSystem(std::string name, ECS::ecsint id):System(name,id){};
//    MOCK_METHOD2(attachComponent,bool(ECS::ecsint cid, ECS::Component *comp));
    MOCK_METHOD0(update,void());
    MOCK_METHOD1(setDelay,void( const std::chrono::duration<double, std::nano> delay));
//    void setDelay( const std::chrono::duration<double, std::nano> delay){};
    System::listype isListener(){return m_listenFunction;}
    bool getUpdate(){return m_update;}
};
class MockComponent:public Component {
public:
    MockComponent(std::string name, ECS::ecsint id):Component(name,id){};

};
#endif // MOCKS_H
