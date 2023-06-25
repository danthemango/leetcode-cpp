#include "../../common/common.h"
#include "../../common/jsonParse.h"
#include "../../common/solutionFunction.h"
#include "../../common/argParse.h"

/*
the solution parser will generate a readme parser

a program should take as input the Solution.h,
and create a runner.cpp with a solution runner.
the solution runner should takes as input the readme,
creates an array of test cases,
each test case has an array of values for input, and one output,
and cast the input values to the expected variable types
needed for the main program.
*/

// returns the function arguments string
std::string argsRunString(const std::vector<std::shared_ptr<SolutionFuncArg>>& args) {
    std::string result;
    bool first = true;
    for(const auto& arg : args) {
        if(!first) {
            result.append(", ");
        } else {
            first = false;
        }
        result.append(arg->name);
        result.append(".get()");
    }
    return result;
}

// prints the runner.cpp file content to stdout based on the function name and args data
int main(int argc, char** argv) {
    ArgParse argParse(argc, argv);
    std::ifstream infile;
    std::ofstream outfile;
    if(argParse.hasHelp()) {
        std::cerr << "usage: -i <infile> -o <outfile>" << std::endl;
        return 1;
    } else if(!argParse.tryParseIOFiles(infile, outfile)) {
        return 1;
    }

    std::string fileContents = file2String(infile);
    auto fileJSON = js::JObject::tryParse(fileContents);
    auto solutionFunction = SolutionFunction::tryParse(fileJSON);

    outfile << "#include \"../../common/common.h\"\n"
        << "#include \"../../common/testCase.h\"\n"
        << "#include \"Solution.h\"\n"
        << '\n'
        << "void runSolution(std::shared_ptr<TestCase> testCase) {\n";

        // print input types
        for(const auto& arg : solutionFunction->args) {
            outfile
                << "    " << arg->testType << " " << arg->name << ";\n"
                << "    if(!" << arg->name << ".tryParse(testCase->input[\"" << arg->name << "\"])) {\n"
                << "        std::cout << \"could not parse input value '" << arg->name << "' from input file\" << std::endl;\n"
                << "        return;\n"
                << "    }\n";
        }

        // print expected value type
        outfile
            << "    " << solutionFunction->testType << " expected;\n"
            << "    if(!expected.tryParse(testCase->expected)) {\n"
            << "        std::cout << \"Could not parse expected value: \" << \"(\" << testCase->expected << \")\" << std::endl;\n"
            << "        return;\n"
            << "    }\n"
            << "\n"
            << "    Solution solution;\n"
            << "    " << solutionFunction->testType << " output(solution." << solutionFunction->name << "(" << argsRunString(solutionFunction->args) << "));\n";

        outfile
            << "    std::cout << *testCase;\n"
            << "    std::cout << \"output: \" << output << std::endl;\n"
            << '\n'
            << "    if(expected == output) {\n"
            << "        std::cout << \"Success.\" << std::endl;\n"
            << "    } else {\n"
            << "        std::cout << \"Fail.\" << std::endl;\n"
            << "    }\n"
            << "    std::cout << std::endl;\n"
            << "}\n"
            << '\n'
            << "int main(int argc, char** argv) {\n"
            << "    try {\n"
            << "        auto in = getStream(\"readme.md\");\n"
            << "        auto testCases = getTestCases(in);\n"
            << "        for(const auto& testCase : testCases) {\n"
            << "            runSolution(testCase);\n"
            << "        }\n"
            << "    } catch (std::exception& e) {\n"
            << "        std::cout << \"exception: \" << e.what() << std::endl;\n"
            << "    } catch (const char* s) {\n"
            << "        std::cout << \"exception: \" << s << std::endl;\n"
            << "    }\n"
            << "}\n";

        infile.close();
        outfile.close();

        return 0;
}