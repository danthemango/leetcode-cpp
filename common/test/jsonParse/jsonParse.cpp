#include "../../common.h"
#include "../../jsonParse.h"
#include "../../inputParse.h"

using namespace js;

/*
    some lovely graphs may be viewed at:
    https://www.json.org/json-en.html
*/

int main() {
    std::string filename = "sample.json";
    std::string fileContents;
    if(!tryGetFileContents(filename, fileContents)) {
        cerr << "could not open " << filename << endl;
        return 1;
    }
    
    // InputParser ip(fileContents);
    InputParser ip("\"hello\"");
    auto je = js::JValue::tryParse(fileContents);
    if(je == nullptr) {
        cerr << "could not parse json in " << filename << endl;
        return 1;
    }

    cout << "Success" << endl;
    cout << je << endl;
}
