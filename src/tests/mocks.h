#ifndef MOCKS_H
#define MOCKS_H
#include "gmock/gmock.h"

#include <chrono>
#include "../ECS/ECS.h"
#include "../ECS/system.cpp"
#include "../ECS/component.cpp"
class MockSystem : public ECS::System {

 public:
    MockSystem(ECS::ecsint id):System(id){};
//    MOCK_METHOD2(attachComponent,bool(ECS::ecsint cid, ECS::Component *comp));
    MOCK_METHOD0(update,void());
    MOCK_METHOD1(setDelay,void( const std::chrono::duration<double, std::nano> delay));
    MOCK_METHOD2(attachComponent, bool(ECS::ecsint cid, Component *comp));
    MOCK_METHOD1(detachComponent, bool(ECS::ecsint cid));
//    void setDelay( const std::chrono::duration<double, std::nano> delay){};
    System::listype isListener(){return m_listenFunction;}
    bool getUpdate(){return m_update;}


};
class MockComponent:public Component {
public:
    MockComponent(ECS::ecsint id):Component(id){};

};
#endif // MOCKS_H
