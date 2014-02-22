#include <gtest/gtest.h>

#include "mocks.h"
namespace {

TEST(SystemTest, TestSystemConcretes) {
  MockSystem system("mocksystem",1);
  MockComponent component("comp",2);

  ASSERT_STREQ(system.name().c_str(),"mocksystem");
  ASSERT_STREQ(component.name().c_str(),"comp");
  ASSERT_EQ(system.attachComponent(1,&component),true);
  ASSERT_EQ(system.attachComponent(1,&component),false);
  ASSERT_EQ(system.detachComponent(1),true);
  ASSERT_EQ(system.detachComponent(1),false);
  ASSERT_EQ(system.entityId(),1);


}
TEST(ListenerTest, ListenerTest)
{
    MockSystem sys("mock",1);
    EXPECT_EQ(sys.isListener(),nullptr);
    sys.addListener([](){});
    EXPECT_NE(sys.isListener(),nullptr);
    std::cout<<"UPDATE::"<<sys.getUpdate()<<std::endl;
}

TEST(MultiComponentTest,TestMultipleComponents)
{
    MockSystem system("mock",1);
    MockComponent component1("comp1",1);
    MockComponent component2("comp2",2);
    MockComponent component3("comp3",3);

    ASSERT_STREQ(component1.name().c_str(),"comp1");
    ASSERT_STREQ(component2.name().c_str(),"comp2");
    ASSERT_STREQ(component3.name().c_str(),"comp3");

    std::unordered_map<ecsint, Component *> compMap = system.compMap();
    EXPECT_EQ(compMap.size(),0);

    EXPECT_EQ(system.attachComponent(1,&component1),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),1);

    EXPECT_EQ(system.attachComponent(2,&component2),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),2);

    EXPECT_EQ(system.attachComponent(3,&component3),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),3);


    EXPECT_EQ(system.detachComponent(1),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),2);

    EXPECT_EQ(system.detachComponent(2),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),1);

    EXPECT_EQ(system.detachComponent(3),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),0);

    ASSERT_STREQ(component1.name().c_str(),"comp1");
    ASSERT_STREQ(component2.name().c_str(),"comp2");
    ASSERT_STREQ(component3.name().c_str(),"comp3");

    EXPECT_EQ(system.detachComponent(1),false);
    EXPECT_EQ(system.detachComponent(2),false);
    EXPECT_EQ(system.detachComponent(3),false);

    EXPECT_EQ(system.attachComponent(1,&component1),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),1);

    EXPECT_EQ(system.attachComponent(2,&component2),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),2);

    EXPECT_EQ(system.attachComponent(3,&component3),true);
    compMap = system.compMap();
    EXPECT_EQ(compMap.size(),3);


    for(auto &c:compMap)
    {
        EXPECT_NE(c.second,nullptr);
    }
}
}
