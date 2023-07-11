#ifndef SOLUTIONFUNCTION_H
#define SOLUTIONFUNCTION_H

#include "common.h"
#include "jsonParse.h"

class SolutionFuncArg {
    public:
    SolutionFuncArg(std::string _name, std::string _basicType, std::string _testType);

    std::string name;
    std::string basicType;
    std::string testType;
};

/*
    parses json for the main solution function
*/
class SolutionFunction {
    private:
    SolutionFunction();

    public:
    std::string name;
    std::string testType;
    std::string basicType;
    std::vector<std::shared_ptr<SolutionFuncArg>> args;

    // returns a pointer to the solution function from a json object, if possible
    static std::shared_ptr<SolutionFunction> tryParse(std::shared_ptr<js::JObject> jObject);
};

#endif // SOLUTIONFUNCTION_H
