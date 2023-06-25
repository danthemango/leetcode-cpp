#include "../../common.h"
#include "../../codeParse.h"

int main() {
    std::string varType;
    std::string variableName;

    codeParse::FunctionDef functionDef;
    std::string input =" std::map<int, std::string> myFunc ( const std :: string hello, std :: \t vector< std::map<int, std::string> > mystrings,int a ) const {int i = 0} ";

    int i = 0;
    if(functionDef.tryParse(input, i)) {
        cout << functionDef.toString() << endl;
    } else {
        cout << "could not parse" << endl;
    }

    cout << endl << "arguments:" << endl;
    cout << "----------" << endl;
    for(const auto& arg : functionDef.args) {
        cout << arg.toString() << endl;
        cout << "- ";

        if(arg.varType == "std::string" || arg.varType == "string") {
            cout << "recognized string" << endl;
        } else {
            cout << "arg type not recognized" << endl;
        }
    }
}

