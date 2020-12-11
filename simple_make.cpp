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
        if (!(*lineIt).size() || (*lineIt) == "\n") continue; 
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

vector<string> readFromStdin()
{
    string line;
    vector<string> allLines;
    while(getline(cin, line)){
        allLines.push_back(line);
    }
    return allLines;
}

int main()
{

    vector<string> allLines = readFromStdin();

    RuleSet rules = RuleSet();
    if (!createRulesetFromInput(allLines, rules))
    {
        cout << "Malformed input, exiting" << endl;
        return 0;
    }

    rules.printRuleSet();
    cout << rules.findRule("target").evaluate(rules) << endl;
}