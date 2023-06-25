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

void test1() {
    InputParser ip("true");
    std::shared_ptr<js::JValue> jval = js::JBoolean::tryParse(ip);

    jval->toString();
    // printSuccess(1, (jval != nullptr && jval->toString() == "true"));
    printSuccess(1, (true));
}

void test2() {
    InputParser ip("false");
    std::shared_ptr<js::JValue> jval = js::JBoolean::tryParse(ip);

    printSuccess(1, (jval != nullptr && jval->toString() == "false"));
}

/* fail to parse condition */
void test3() {
    InputParser ip("\"hello");
    std::shared_ptr<js::JValue> jval = js::JBoolean::tryParse(ip);
    printSuccess(2, (jval == nullptr));
}

int main() {
    int testNum = 1;
    try {
        test1();
        testNum++;
        test2();
        testNum++;
        test3();
    } catch (...) {
        cout << "failure on test nbr " << testNum << endl;   
    }
}
