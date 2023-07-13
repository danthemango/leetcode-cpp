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
    unsigned int i = 0;
    std::string inputSC = stripComments(input);
    auto classDef = std::make_shared<ClassDef>();

    // create a list of classes, and fetch class Solution after
    std::vector<std::shared_ptr<ClassDef>> classDefs;

    while(i < inputSC.size()) {
        if(classDef->tryParse(inputSC, i)) {
            classDefs.push_back(classDef);
            classDef = std::make_shared<ClassDef>();
        } else {
            ++i;
        }
    }

    bool found = false;
    for(const auto& def : classDefs) {
        if(def->name == "Solution") {
            classDef = def;
            found = true;
        }
    }
    if(!found) {
        std::cerr << "Error (solution2json.cpp): could not find solution" << endl;
        return false;
    }

    auto funcs = classDef->getMemberFuncByAccess(AccessLevel::_public);
    if(funcs.size() == 0) {
        std::cerr << "Error (solution2json.cpp): could not find solution function (is it private?)" << endl;
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
    std::string infileName;
    std::string outfileName;
    if(argParse.hasHelp()) {
        std::cerr << "usage: -i <infile> -o <outfile>" << endl;
        return 1;
    } else if(!argParse.tryParseIOFileNames(infileName, outfileName)) {
        return 1;
    } 

    std::ifstream infile;
    infile.open(infileName);
    if (!infile.is_open())
    {
        std::cerr << "could not open infile" << endl;
        std::cerr << infileName << endl;
        return false;
    }
    std::string fileContents = file2String(infile);
    std::string jsonString;
    if(!parseSolutionClass(fileContents, jsonString)) {
        infile.close();
        return 1;
    }

    std::ofstream outfile;
    outfile.open(outfileName);
    if (!outfile.is_open())
    {
        std::cerr << "could not open outfile" << endl;
        return false;
    }

    outfile << jsonString;
    infile.close();
    outfile.close();
    return 0;
}
