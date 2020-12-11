#include <iostream>
#include <string>
#include "../Rules.h"
#include "../input_utils.h"
#include <gtest/gtest.h>

using namespace std;

class RuleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }
    Rule r1 = Rule ("target", {"dep1", "dep2"}, "cmd1");
    Rule r2 = Rule ("dep1", {"dep2"}, "cmd2");
    Rule r3 = Rule ("dep2", {""}, "cmd3");
    Rule r4 = Rule ("dep2", {" "}, "cmd4");
};

TEST_F(RuleTest, InitializationTest)
{
    EXPECT_EQ(r1.getTarget(), "target");
    EXPECT_EQ(r2.getTarget(), "dep1");
    
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
