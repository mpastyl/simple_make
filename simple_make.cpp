#include "simple_make.h"

using namespace std;

string Rule::evaluate(RuleSet& rules) 
{
    if (!dependencies.size())
    {
        return "Target: " + target + " evaluates to: " + command + "\n";
    }
    else
    {
        string res;
        for (auto dep: dependencies)
        {
            res += rules.findRule(dep).evaluate(rules);
        }
        return res;
    }
}

void RuleSet::addRule(Rule rule)
{
    rules.push_back(rule);
}

Rule& RuleSet::findRule(string target)
{
    for (auto& rule : rules)
    {
        if (rule.getTarget() == target)
        {
            return rule;
        }
    }
    cout << "Could not solve dependency: " + target << endl;
    return rules[0];
}

int main()
{
    Rule r1 = Rule("target1", {"dep1", "dep2"}, "cmd1");
    Rule r2 = Rule("dep1", {"dep2"}, "cmd2");
    Rule r3 = Rule("dep2", {}, "cmd3");

    RuleSet rules = RuleSet();
    rules.addRule(r1);
    rules.addRule(r2);
    rules.addRule(r3);

    


    cout << r3.evaluate(rules) << endl;
    //cout << rules.findRule("target").evaluate(rules) << endl;
}