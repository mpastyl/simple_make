#include "simple_make.h"

using namespace std;

int main()
{

    vector<string> allLines = readFromStdin();

    RuleSet rules = RuleSet();
    if (!createRulesetFromInput(allLines, rules))
    {
        cout << "Malformed input, exiting" << endl;
        return 0;
    }

    //rules.printRuleSet();
    Rule firstRule = rules.findRule(rules.getFirstTarget());
    cout << firstRule.evaluate(rules) << endl;
}