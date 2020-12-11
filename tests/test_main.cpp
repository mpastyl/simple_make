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
    EXPECT_EQ(r4.getTarget(), "dep2");
    
}

class RuleSetTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        rules.addRule(r1);
        rules.addRule(r2);
        rules.addRule(r3);
        rules.addRule(r4);
        rules.addRule(r5);
    }
    RuleSet rules = RuleSet();
    Rule r1 = Rule ("target", {"dep1", "dep2"}, "\tcmd1");
    Rule r2 = Rule ("dep1", {"dep3", "dep4"}, "\tcmd2");
    Rule r3 = Rule ("dep3", {""}, "\tcmd3");
    Rule r4 = Rule ("dep4", {""}, "\tcmd4");
    Rule r5 = Rule ("dep2", {""}, "\tcmd5");
};


TEST_F(RuleSetTest, FindRulesTest)
{   
    EXPECT_EQ(rules.findRule("dep1").getTarget(), "dep1");

}


TEST_F(RuleSetTest, FindFirstTarget)
{   
    EXPECT_EQ(rules.getFirstTarget(), "target");
}

TEST_F(RuleSetTest, EvaluationTests)
{
    string expected = "\tcmd3\n\tcmd4\n\tcmd2\n\tcmd5\n\tcmd1\n";
    string firstTarget  = rules.getFirstTarget();
    EXPECT_EQ(rules.findRule(firstTarget).evaluate(rules), expected);
}


class InputTests : public ::testing::Test
{
protected:
    RuleSet rules = RuleSet();
    vector<string> proper = {"target: dep1", "\tcmd1", "dep1: ", "\tcmd2"};
    vector<string> proper_auto_var = {"target: dep1", "\tcmd1 $@", "dep1: ", "\tcmd2"};
    vector<string> proper_empty_lines = {"\n", 
                                        "target: dep1", 
                                        "\tcmd1", 
                                        "\n", 
                                        "\n",
                                        " dep1: ", 
                                        "\tcmd2",
                                        "\n", 
                                        "\n"};
    vector<string> proper_spaces = {"target: dep1      dep2", "\tcmd1", "dep1: ", "\tcmd2", "dep2: ", "\tcmd3"};
    vector<string> missing_command = {"target: dep1", "dep1: ", "\tcmd2"};    
    vector<string> missing_target = {": dep1", "dep1: ", "\tcmd2"};
};


TEST_F(InputTests, ProperInput)
{
    EXPECT_EQ(createRulesetFromInput(proper,rules), 1);
    EXPECT_EQ(createRulesetFromInput(proper_empty_lines,rules), 1);
    EXPECT_EQ(createRulesetFromInput(proper_spaces,rules), 1);
}

TEST_F(InputTests, MalformedInput)
{
    EXPECT_EQ(createRulesetFromInput(missing_command,rules), 0);
    EXPECT_EQ(createRulesetFromInput(missing_target,rules), 0);
}


TEST_F(InputTests, AutoVar)
{
    createRulesetFromInput(proper_auto_var, rules);
    string expected = "\tcmd2\n\tcmd1 target\n";
    string firstTarget  = rules.getFirstTarget();
    EXPECT_EQ(rules.findRule(firstTarget).evaluate(rules), expected);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
