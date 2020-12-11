#ifndef __SIMPLE_MAKE_H
#define __SIMPLE_MAKE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RuleSet;

class Rule
{
    public:
        //Rule() : target(""), dependencies({""}), command(""), isEvaluated(false), evaluatesTo("") {};
        Rule(string target, vector<string> deps, string command) : target(target), dependencies(deps), command(command), isEvaluated(false), evaluatesTo("") {};
        string getTarget() {return target;}
        string evaluate(RuleSet&);
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
        RuleSet() : rules({}) {};
        void addRule(Rule rule);
        Rule& findRule(string target);
        void printRuleSet();
    private:
        vector<Rule> rules;
};

#endif //__SIMPLE_MAKE_H