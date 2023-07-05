using namespace std;

#include "../../common/common.h"
#include "../../common/codeParse.h"
#include "../../common/jsonParse.h"
#include "../../common/testCase.h"
#include "../../common/argParse.h"
using namespace textParse;
using namespace codeParse;
using namespace std;

/*
    takes a cpp file, parses it for a solution class,
    and parses the last member function for its return type
    and funciton argument names and types,
    returning true if successful and setting the out_json
*/
bool parseSolutionClass(const std::string& input, std::string& out_json) {
    int i = 0;
    std::string inputSC = stripComments(input);
    ClassDef classDef;

    while(i < inputSC.size() && !classDef.tryParse(inputSC, i) && classDef.name != "Solution") {
        ++i;
    }

    if(classDef.name != "Solution") {
        std::cerr << "Error (solution2json.cpp): could not find solution" << endl;
        return false;
    }

    auto funcs = classDef.getMemberFuncByAccess(AccessLevel::_public);
    if(funcs.size() == 0) {
        std::cerr << "Error (solution2json.cpp): could not find solution function" << endl;
        return false;
    }

    auto func = funcs[funcs.size() - 1];

    using namespace js;
    auto funcObj = std::shared_ptr<JObject>(new JObject());
    funcObj->set("name", func.functionDef.name);
    std::string funcBasicType = func.functionDef.returnType.toString(false);
    funcObj->set("basicType", funcBasicType);
    std::string funcTestType;
    if(!tryParseTestType(funcBasicType, funcTestType)) {
        return false;
    }
    funcObj->set("testType", funcTestType);

    auto argArray = std::shared_ptr<JArray>(new JArray());
    funcObj->set("args", argArray);
    for(const auto& arg : func.functionDef.args) {
        std::string argName = arg.name;
        std::string typeString = arg.varType.toString(false);
        std::string testTypeString;
        if(!tryParseTestType(typeString, testTypeString)) {
            return false;
        }

        auto argObj = std::shared_ptr<JObject>(new JObject());
        argObj->set("name", argName);
        argObj->set("basicType", typeString);
        argObj->set("testType", testTypeString);
        argArray->push_back(argObj);
    }
    out_json = funcObj->toString();
    return true;
}

int main(int argc, char** argv) {
    ArgParse argParse(argc, argv);
    std::ifstream infile;
    std::ofstream outfile;
    if(argParse.hasHelp()) {
        std::cerr << "usage: -i <infile> -o <outfile>" << endl;
        return 1;
    } else if(!argParse.tryParseIOFiles(infile, outfile)) {
        return 1;
    }
    std::string fileContents = file2String(infile);
    std::string jsonString;
    if(!parseSolutionClass(fileContents, jsonString)) {
        infile.close();
        outfile.close();
        return 1;
    }
    outfile << jsonString;
    infile.close();
    outfile.close();
    return 0;
}
