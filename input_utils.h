#ifndef __INPUT_UTILS_H
#define __INPUT_UTILS_H

#include <regex>
#include "Rules.h"

using namespace std;

vector<string> tokenize(string sRaw, string delimiter)
{
    vector<string> retList;
    size_t pos = 0;
    string token;
    while ((pos = sRaw.find(delimiter)) != string::npos)
    {
        token = sRaw.substr(0, pos);
        if (token.size())
            retList.push_back(token);
        sRaw.erase(0, pos + delimiter.length());
    }
    retList.push_back(sRaw);
    return retList;
}

//Files "rules" with rules extracted from "lines". "lines" holds each line of the input.
int createRulesetFromInput(vector<string> lines, RuleSet &rules)
{
    for (auto lineIt = lines.begin(); lineIt != lines.end(); lineIt++)
    {
        //Ignore empty lines
        if (!(*lineIt).size() || (*lineIt) == "\n")
            continue;
        //This line should contain target and deps
        string line = *lineIt;
        vector<string> split_column = tokenize(line, ":");
        if (split_column.size() != 2)
        {
            cerr << "malformed rule: " << line << endl;
            return 0;
        }
        string target = split_column[0];

        if (!target.size())
        {
            cerr << "malformed rule, cant find target from rule:" << line << endl;
            return 0;
        }

        string depsRaw = split_column[1];
        vector<string> depList = tokenize(depsRaw, " ");

        //Moving to the next line, it should contain the command
        if (++lineIt != lines.end())
        {
            line = *lineIt;
            if (line[0] != '\t')
            {
                cerr << "Should start with tab" << endl;
                cerr << "Got: " << line << endl;
                return 0;
            }
            string command = line;
            command = regex_replace(command, regex("\\$@"), target);
            command = regex_replace(command, regex("\\$<"), depList[0]);
            for (auto &dep : depList)
            {
                dep = regex_replace(dep, regex("\\$@"), target);
            }
            string all_deps = "";
            for (auto &dep : depList)
            {
                all_deps += dep + " ";
            }
            command = regex_replace(command, regex("\\$\\?"), all_deps);
            Rule new_rule = Rule(target, depList, command);
            rules.addRule(new_rule);
        }
        else
        {
            cerr << "Missing last command" << endl;
            return 0;
        }
    }
    return 1;
}

vector<string> readFromStdin()
{
    string line;
    vector<string> allLines;
    while (getline(cin, line))
    {
        allLines.push_back(line);
    }
    return allLines;
}

#endif //__INPUT_UTILS_H