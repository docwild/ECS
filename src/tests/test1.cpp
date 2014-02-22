#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include "../myecs/component_factory.h"
#include "../myecs/systemfactory.h"
#include "../ECS/systemmanager.h"

namespace {

// The fixture for testing class Foo.
class CompFactTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.


  // Objects declared here can be used by all tests in the test case for CompFact.
    std::unique_ptr<ECS::Component> cfup;
    CompFactory cf;
};

// Tests that Speed isnt a nullptr
TEST_F(CompFactTest, CheckSpd) {

    cfup = cf(CENUM::CSPEED,"CSPEED",1);
    ASSERT_NE(nullptr, cfup);
    EXPECT_STREQ("CSPEED",cfup->name().c_str());
}


// Tests that Pos isnt a nullptr
TEST_F(CompFactTest, CheckPos) {
    std::string nm = "CPOSITION";
    cfup = cf(CENUM::CPOSITION,nm,1);
    ASSERT_NE(nullptr, cfup);
    EXPECT_STREQ(nm.c_str(),cfup->name().c_str())<< nm<<" = " << ::testing::PrintToString(cfup->name());
}

// Tests that unknown is a nullptr
TEST_F(CompFactTest, Checknull) {

    cfup = cf(55,"UNKNOWN",1);
    ASSERT_EQ(nullptr, cfup);

}
}  // namespace
namespace
{
class SysFactTest: public ::testing::Test
{
protected:
    SysFactTest():sf(),cf(),sysman(MAX,cf,sf)
    {


        ok &= sysman.registerType(CENUM::CPOSITION,"Position",sysman.compTypes());
        ok &= sysman.registerType(CENUM::CSPEED,"Speed",sysman.compTypes());
        ok &= sysman.registerType(SENUM::SMOVEMENT,"Movement",sysman.sysTypes());
    }
    bool ok{true};
    std::unique_ptr<ECS::System> sfup;
    SystemFactory sf;
    CompFactory cf;
    ECS::SystemManager sysman;
    const ECS::ecsint MAX = 500;
};

TEST_F(SysFactTest, CheckMovement)
{
    sfup = sf(SENUM::SMOVEMENT,"SMOVEMENT",1);
    ASSERT_NE(nullptr,sfup);
}
TEST_F(SysFactTest, CheckSysMan)
{

    ASSERT_TRUE(ok);
    const ECS::ecsint play = sysman.addEntity(SENUM::SMOVEMENT,
                                              CENUM::CPOSITION|CENUM::CSPEED);
    ASSERT_NE(play,MAX);
    ECS::SMovement *smo = sf.getMovementSystem(play,sysman);
    ASSERT_NE(nullptr,smo);
}


TEST_F(SysFactTest,CheckTooManyEntities)
{
    ASSERT_TRUE(ok);
    for(int x = 1; x < MAX; x++)
    {
        int p = sysman.addEntity(SENUM::SMOVEMENT,
                                 CENUM::CPOSITION|CENUM::CSPEED);
        ASSERT_NE(p,MAX);
    }
    ASSERT_THROW(int p = sysman.addEntity(SENUM::SMOVEMENT,
                                          CENUM::CPOSITION|CENUM::CSPEED),std::exception);


}

}
//--gtest_filter=CompFactTest*:SysFactTest.*-SysFactTest.CheckTooManyEntities: --gtest_catch_exceptions=
