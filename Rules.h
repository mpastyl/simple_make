#ifndef __RULES_H
#define __RULES_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class RuleSet;

class Rule
{
    public:
        Rule() : target(""), dependencies({""}), command(""), isEvaluated(false), evaluatesTo("") {};
        Rule(string target, vector<string> deps, string command) : target(target), dependencies(deps), command(command), isEvaluated(false), evaluatesTo("") {};
        string getTarget() {return target;}
        string evaluate(RuleSet&, unordered_set<string> = unordered_set<string>());
        void printRule();
    private:
        string target;
        vector<string> dependencies;
        string command;
        bool isEvaluated;
        string evaluatesTo;
};

class RuleSet
{
    public:
        RuleSet() : rules(unordered_map<string, Rule>()), firstTarget("") {};
        void addRule(Rule rule);
        Rule& findRule(string target);
        void printRuleSet();
        string getFirstTarget() {return firstTarget;}
    private:
        unordered_map<string, Rule> rules;
        string firstTarget;
};

#endif //__RULES_H