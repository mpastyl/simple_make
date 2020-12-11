#include "simple_make.h"

using namespace std;

string Rule::evaluate(RuleSet& rules) 
{
    if (isEvaluated) return "";
    string res = "";
    if (dependencies.size())
    {
        for (auto dep: dependencies)
        {
            if (dep.size())
                res += rules.findRule(dep).evaluate(rules);
        }
    }
    res += "Target: " + target + " evaluates to: " + command + "\n";
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

void RuleSet::printRuleSet()
{
    for (auto rule : rules){
        cout << "----" << endl;
        rule.printRule();
    }
}

vector<string> tokenize(string sRaw, string delimiter)
{
    vector<string> retList;
    size_t pos = 0;
    string token;
    while ((pos = sRaw.find(delimiter)) != string::npos) {
        token = sRaw.substr(0, pos);
        if (token.size()) retList.push_back(token);
        sRaw.erase(0, pos + delimiter.length());
    }
    retList.push_back(sRaw);
    return retList;
}

//Files "rules" with rules extracted from "lines". "lines" holds each line of the input.
int createRulesetFromInput(vector<string>lines, RuleSet& rules)
{
    for (auto lineIt=lines.begin(); lineIt != lines.end(); lineIt++)
    {
        //TODO: ignore empty lines 

        //This line should contain target and deps
        string line = *lineIt;
        vector<string> split_column = tokenize(line, ":");
        string target = split_column[0];
        
        string depsRaw = split_column[1];
        vector<string> depList = tokenize(depsRaw, " ");

        //Moving to the next line, it should contain the command
        if (lineIt++ != lines.end())
        {
            line =  *lineIt;
            if (line[0]!='\t')
            {
                cout << "Should start with tab" << endl;
                cout << "Got: " << line << endl;
                return 0;
            }
            string command =  line;
            Rule new_rule = Rule(target, depList, command);
            rules.addRule(new_rule);
        }
        else{
            cout << "Missing last command" << endl;
            return 0;
        }
        
    }
    return 1;
}

int main()
{
    string l1 = "target: dep1 dep2";
    string l2 = "\tcmd1";
    string l3 = "dep1: dep2";
    string l4 = "\tcmd2";
    string l5 = "dep2: ";
    string l6 = "\tcmd3";

    //Rule r1 = Rule("target1", {"dep1", "dep2"}, "cmd1");
    //Rule r2 = Rule("dep1", {"dep2"}, "cmd2");
    //Rule r3 = Rule("dep2", {}, "cmd3");

    RuleSet rules = RuleSet();
    if (!createRulesetFromInput({l1, l2, l3, l4, l5, l6}, rules))
    {
        cout << "Malformed input, exiting" << endl;
        return 0;
    }
    
    //rules.addRule(r1);
    //rules.addRule(r2);
    //rules.addRule(r3);

    

    rules.printRuleSet();
    //cout << r1.evaluate(rules) << endl;
    cout << rules.findRule("target").evaluate(rules) << endl;
}