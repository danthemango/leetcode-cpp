#include "../../common.h"
#include "../../codeParse.h"
using namespace codeParse;

std::string solutionString = "\
class Solution {\n\
    /*\n\
        create a map of found numbers with their indices\n\
        iterate through each element,\n\
        and for each element, get the associated other number needed\n\
        (remainder = target - nums[i])\n\
        if the needed number exists in the map, return the answer:\n\
        - the current index, and the index of the val in the map\n\
        \n\
    */\n\
private:\n\
    int a = 5;\n\
\
public:\n\
    vector<int> twoSum(vector<int>& nums, int target) {\n\
        vector<int> result;\n\
        // val -> index\n\
        map<int, int> foundNums;\n\
        \n\
        for(int i = 0; i < nums.size(); i++) {\n\
            // remainder\n\
            int rem = target - nums[i];\n\
            if(foundNums.find(rem) != foundNums.end()) {\n\
                // we found the needed number, returns its index\n\
                int remIndex = foundNums[rem];\n\
                result.push_back(i);\n\
                result.push_back(remIndex);\n\
                return result;\n\
            } else {\n\
                // else insert the num into the map\n\
                foundNums[nums[i]] = i;\n\
            }\n\
        }\n\
        return result;\n\
    }\n\
};\n\
";


int main() {
    std::string solutionWOComment = stripComments(solutionString);

    ClassDef classDef;
    int i = 0;
    if(!classDef.tryParse(solutionWOComment, i)) {
        cerr << "could not parse class" << endl;
        return 1;
    }

    cout << classDef.name << endl;
    auto funcs = classDef.getMemberFuncByAccess(AccessLevel::_public);
    if(funcs.size() == 0) {
        cout << "could not get function" << endl;
        return 1;
    }

    auto func = funcs[funcs.size()-1];
    cout << func.functionDef.name << endl;
    for(const auto& arg : func.functionDef.args) {
        cout << "- " << arg.toString() << endl;
    }

    cout << classDef.toString() << endl;
    return 0;
}
