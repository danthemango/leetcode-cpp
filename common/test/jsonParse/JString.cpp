#include "../../common.h"
#include "../../jsonParse.h"
#include "../../inputParse.h"

/* specifies if the test was a success or failure */
void printSuccess(int testNum, bool test) {
    cout << "Test " << testNum << ": ";
    if(test) {
        cout << "success" << endl;
    } else {
        cout << "failure" << endl;
    }
}

/* successful parse condition */
void test1() {
    InputParser ip("\"hello\"");
    std::shared_ptr<js::JValue> jval = js::JString::tryParse(ip);

    printSuccess(1, (jval != nullptr && jval->toString() == "\"hello\""));
}

/* fail to parse condition */
void test2() {
    InputParser ip("\"hello");
    std::shared_ptr<js::JValue> jval = js::JString::tryParse(ip);
    printSuccess(2, (jval == nullptr));
}

int main() {
    test1();
    test2();
}
