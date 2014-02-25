#include <gtest/gtest.h>

#include "mocks.h"
namespace {
using ::testing::_;
using ::testing::Return;
TEST(SystemTest, TestSystemConcretes) {
  MockSystem system(1);
  MockComponent component(2);
  EXPECT_CALL(system, attachComponent(_,_))
      .WillOnce(Return(true))
      .WillOnce(Return(false));
  EXPECT_CALL(system, detachComponent(_))
      .WillOnce(Return(true))
      .WillOnce(Return(false));
//  ASSERT_STREQ(system.name().c_str(),"mocksystem");
//  ASSERT_STREQ(component.name().c_str(),"comp");
  ASSERT_EQ(system.attachComponent(1,&component),true);
  ASSERT_EQ(system.attachComponent(1,&component),false);
  ASSERT_EQ(system.detachComponent(1),true);
  ASSERT_EQ(system.detachComponent(1),false);
  ASSERT_EQ(system.entityId(),1);


}
TEST(ListenerTest, ListenerTest)
{
    MockSystem sys(1);
    EXPECT_EQ(sys.isListener(),nullptr);
    sys.addListener([](){});
    EXPECT_NE(sys.isListener(),nullptr);
    std::cout<<"UPDATE::"<<sys.getUpdate()<<std::endl;
}

//TEST(MultiComponentTest,TestMultipleComponents)
//{
//    MockSystem system(1);
//    MockComponent component1(1);
//    MockComponent component2(2);
//    MockComponent component3(3);

////    ASSERT_STREQ(component1.name().c_str(),"comp1");
////    ASSERT_STREQ(component2.name().c_str(),"comp2");
////    ASSERT_STREQ(component3.name().c_str(),"comp3");

//    std::unordered_map<ecsint, std::unique_ptr<Component>> *compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),0);

//    EXPECT_EQ(system.attachComponent(1,&component1),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),1);

//    EXPECT_EQ(system.attachComponent(2,&component2),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),2);

//    EXPECT_EQ(system.attachComponent(3,&component3),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),3);


//    EXPECT_EQ(system.detachComponent(1),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),2);

//    EXPECT_EQ(system.detachComponent(2),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),1);

//    EXPECT_EQ(system.detachComponent(3),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),0);

//    ASSERT_STREQ(component1.name().c_str(),"comp1");
//    ASSERT_STREQ(component2.name().c_str(),"comp2");
//    ASSERT_STREQ(component3.name().c_str(),"comp3");

//    EXPECT_EQ(system.detachComponent(1),false);
//    EXPECT_EQ(system.detachComponent(2),false);
//    EXPECT_EQ(system.detachComponent(3),false);

//    EXPECT_EQ(system.attachComponent(1,&component1),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),1);

//    EXPECT_EQ(system.attachComponent(2,&component2),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),2);

//    EXPECT_EQ(system.attachComponent(3,&component3),true);
//    compMap = system.cmap();
//    EXPECT_EQ(compMap->size(),3);


//    for(auto &c:*compMap)
//    {
//        EXPECT_NE(c.second,nullptr);
//    }
//}
}
