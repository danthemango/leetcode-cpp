#include "solutionFunction.h"

SolutionFuncArg::SolutionFuncArg(std::string _name, std::string _basicType, std::string _testType) {
    name = _name;
    basicType = _basicType;
    testType = _testType;
}

/*
    parses json for the main solution function
*/
SolutionFunction::SolutionFunction() { }

// returns a pointer to the solution function from a json object, if possible
std::shared_ptr<SolutionFunction> SolutionFunction::tryParse(std::shared_ptr<js::JObject> jObject) {
    auto solutionFunction = std::shared_ptr<SolutionFunction>(new SolutionFunction());
    if(jObject->getType() != "object") {
        cerr << "SolutionFunction: could not get object" << endl;
        return nullptr;
    }

    if(jObject->get("name") == nullptr) {
        cerr << "SolutionFunction: could not get function name" << endl;
        return nullptr;
    }
    if(!jObject->has("basicType")) {
        cerr << "SolutionFunction: could not parse function basicType" << endl;
        return nullptr;
    }
    if(!jObject->has("testType")) {
        cerr << "SolutionFunction: could not parse function testType" << endl;
        return nullptr;
    }

    auto funcJName = js::toJString(jObject->get("name"));
    solutionFunction->name = funcJName->get();

    auto funcJBasicType = js::toJString(jObject->get("basicType"));
    solutionFunction->basicType = funcJBasicType->get();

    auto funcJTestType = js::toJString(jObject->get("testType"));
    solutionFunction->testType = funcJTestType->get();

    if(jObject->get("args") == nullptr) {
        cerr << "SolutionFunction: could not get function args" << endl;
        return nullptr;
    }
    auto argsArray = js::toJArray(jObject->get("args"));
    if(argsArray->getType() != "array") {
        cerr << "SolutionFunction: could not parse function args" << endl;
        return nullptr;
    }
    
    for(int i = 0; i < argsArray->size(); i++) {
        auto argObject = js::toJObject(argsArray->get(i));
        if(argObject->getType() != "object") {
            cerr << "SolutionFunction: could not parse function arg " << i << endl;
            return nullptr;
        }
        
        if(!argObject->has("name")) {
            cerr << "SolutionFunction: could not parse function arg name" << endl;
            return nullptr;
        }
        if(!argObject->has("basicType")) {
            cerr << "SolutionFunction: could not parse function arg basicType" << endl;
            return nullptr;
        }
        if(!argObject->has("testType")) {
            cerr << "SolutionFunction: could not parse function arg testType" << endl;
            return nullptr;
        }

        auto argJName = js::toJString(argObject->get("name"));
        std::string name = argJName->get();
        auto argJBasicType = js::toJString(argObject->get("basicType"));
        std::string basicType = argJBasicType->get();
        auto argJTestType = js::toJString(argObject->get("testType"));
        std::string testType = argJTestType->get();
        auto arg = std::shared_ptr<SolutionFuncArg> (new SolutionFuncArg(name, basicType, testType));
        solutionFunction->args.push_back(arg);
    }
    return solutionFunction;
}
