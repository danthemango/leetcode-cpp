#include "../../common.h"
#include "../../jsonParse.h"
#include "../../solutionFunction.h"

int main() {
    std::string filename = "sample.json";
    std::string fileContents;
    if(!tryGetFileContents(filename, fileContents)) {
        cerr << "could not open " << filename << endl;
        return 1;
    }
    auto fileJSON = js::JObject::tryParse(fileContents);
    auto sf = SolutionFunction::tryParse(fileJSON);
    cout << "done." << endl;
}
