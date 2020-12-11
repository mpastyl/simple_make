#include "Rules.h"

string Rule::evaluate(RuleSet& rules, unordered_set<string> visited) 
{
    if (isEvaluated) return "";
    //If we have already visited this target, there is a circular dependency
    auto search = visited.find(target);
    if (search != visited.end())
    {
        cout << "Deteced circular dependencies, aborting" << endl;
        exit(0);
    }
    visited.insert(target);
    string res = "";
    if (dependencies.size())
    {
        for (auto dep: dependencies)
        {
            if (dep.size())
                res += rules.findRule(dep).evaluate(rules, visited);
        }
    }
    res += command + "\n";
    isEvaluated = true;
    return res;
}

void Rule::printRule()
{
    cout << "Rule: " << endl;
    cout << "Target: " << target << endl;
    cout << "Dependencies: ";
    for (auto dep: dependencies) cout << dep << " ";
    cout << endl;
    cout << "Command: " << command << endl;  
}

void RuleSet::addRule(Rule rule)
{
    if (!rules.size())
    {
        firstTarget = rule.getTarget();
    } 
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
    //TODO: Need a better return value for when the target is not found
    cout << "Could not find rule for target: " + target << endl;
    exit(0);
}

void RuleSet::printRuleSet()
{
    for (auto rule : rules){
        cout << "----" << endl;
        rule.printRule();
    }
}