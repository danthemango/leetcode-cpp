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
    const int testNum = 1;
    InputParser ip("null");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(1, (jval != nullptr && jval->toString() == "null"));
}

/* fail test condition */
void test2() {
    const int testNum = 2;
    InputParser ip("nul");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval == nullptr));
}

void test3() {
    const int testNum = 3;
    InputParser ip("{}");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test4() {
    const int testNum = 4;
    InputParser ip("[]");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test5() {
    const int testNum = 5;
    InputParser ip("4");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test6() {
    const int testNum = 6;
    InputParser ip("\"hello\"");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test7() {
    const int testNum = 7;
    InputParser ip("[5]");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test8() {
    const int testNum = 8;
    InputParser ip("[5,6]");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test9() {
    const int testNum = 9;
    InputParser ip("[5,\"hello\"]");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test10() {
    const int testNum = 10;
    InputParser ip("{\"hello\": \"world\"}");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test11() {
    const int testNum = 11;
    InputParser ip("{\"myStr\": \"world\", \"myNum\": 5, \"myNull\": null, \"myBool1\": true, \"myBool2\": false}");
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}

void test12() {
    const int testNum = 12;
    std::string input = "\
{\n\
    \"myBool1\": true,\n\
    \"myBool2\": false,\n\
    \"myNull\": null,\n\
    \"myNum\": 5,\n\
    \"myStr\": \"world\"\n\
}\n\
";

    InputParser ip(input);
    std::shared_ptr<js::JValue> jval = js::JValue::tryParse(ip);

    printSuccess(testNum, (jval != nullptr));
}


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
}
