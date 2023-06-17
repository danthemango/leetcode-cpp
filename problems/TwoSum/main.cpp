#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#include "../../common/textParse.h"
using namespace textParse;

/*
    Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

    You may assume that each input would have exactly one solution, and you may not use the same element twice.

    You can return the answer in any order.
*/

class Solution {
public:
    /*
        create a map of found numbers with their indices
        iterate through each element,
        and for each element, get the associated other number needed
        (remainder = target - nums[i])
        if the needed number exists in the map, return the answer:
        - the current index, and the index of the val in the map
        
    */

    // returns a vector of two ints
    vector<int> getDoubleVector(int a, int b) {
        std::vector<int> result;
        result.push_back(a);
        result.push_back(b);
        return result;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        // val -> index
        map<int, int> foundNums;
        
        for(int i = 0; i < nums.size(); i++) {
            // remainder
            int rem = target - nums[i];

            if(foundNums.find(rem) != foundNums.end()) {
                // we found the needed number, returns its index
                return getDoubleVector(i, foundNums[rem]);
            }

            // else insert the num into the map
            foundNums[nums[i]] = i;
        }
        return result;
    }
};

bool tryParseVectorInt(std::string input, int& i, std::vector<int>& out_list) {
    int resetI = i;
    if(!tryParseNextChar(input, i, '[')) {
        i = resetI;
        return false;
    }
    
    bool expectComma = false;

    while(i <= input.size()) {
        int val;
        if(tryParseNextChar(input, i, ']')) {
            return true;
        } else if(expectComma) {
            if(tryParseNextChar(input, i, ',')) {
                expectComma = false;
            } else {
                i = resetI;
                return false;
            }
        } else if(tryParseInt(input, i, val)) {
            out_list.push_back(val);
            expectComma = true;
        } else {
            i = resetI;
            return false;
        }
    }

    i = resetI;
    return false;
}

std::string vectorInt2String(vector<int> input) {
    std::stringstream ss;
    std::string result;
    ss << '[';
    bool first = true;
    for(const int & val : input) {
        if(!first) {
            ss  << ',';
        } else {
            first = false;
        }
        ss << val;
    }
    ss << ']';
    ss >> result;
    return result;
}

// try to parse a string value in a string
// updating i to the char after a validly parsed result
bool tryParseString(std::string input, int& i, std::string& out_content) {
    /*
        after parsing a double-quote,
        add each char to out_content assuming until a non-escaped double-quote is found
    */

    int resetI = i;
    if(!tryParseNextChar(input, i, '"')) {
        i = resetI;
        return false;
    }
    
    // if true, escape the next char
    bool isEscaped = false;
    while(i <= input.size()) {
        int val;
        if(isEscaped) {
            char c = input[i];
            i++;
            char symbol = c;
            // TODO add more of the escaped char symbols
            switch(c) {
                case 'n':
                    symbol = '\n';
                    break;
                case 't':
                    symbol = '\t';
                    break;
                case 'r':
                    symbol = '\r';
                    break;
            }
            out_content.push_back(symbol);
        } else if(tryParseNextChar(input, i, '\\')) {
            isEscaped = true;
        } else if(tryParseNextChar(input, i, '"')) {
            return true;
        } else {
            out_content.push_back(input[i]);
            i++;
        }
    }

    i = resetI;
    return false;
}

// input type specifiation
enum class ArgType {
    _string,
    _int,
    _double,
    _vectorInt,
    _vectorString
};

// one value with any input type
class InputValue {
    public:
    ArgType argType;

    std::string stringVal;
    int intVal;
    double doubleVal;
    std::vector<int> vectorIntVal;
    std::vector<std::string> vectorStringVal;
};

// key-value pairs of input values
class InputMap {
    public:
    std::map<std::string, InputValue> theMap;
    void set(std::string key, InputValue val) {
        theMap[key] = val;
    }

    bool hasKey(std::string key) {
        return theMap.find(key) != theMap.end();
    }

    InputValue get(std::string key) {
        return theMap[key];
    }
};

// attempts to parse input name of the format 'name = val'
// note: using variable naming rules, expecting a space, newline, or '=' after
// updating i to the char after a successful parse
bool tryParseInputName(std::string input, int& i, std::string& out_name) {
    bool first = true;
    int resetI = i;
    while(i < input.size()) {
        char c = input[i];
        if(first) {
            first = false;
            if('0' <= c && c <= '9') {
                i = resetI;
                return false;
            }
        } else {
            if(c == ' ' || c == '\t' || c == '\n' || c == '=') {
                return true;
            }
        }

        if(c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            out_name.push_back(c);
        } else {
            i = resetI;
            return false;
        }

        i++;
    }

    i = resetI;
    return false;
}

// states of comment parsing
enum class CommentState {
    // not inside of a comment
    none,
    // one slash seen, possibly starting a new comment
    noneSlash,
    // inside of a single-line comment
    singleLineComment,
    // inside of a multi-line comment
    multiLineComment,
    // inside of a multi-line comment, and after a star-symbol
    multiStar,
    // inside of a string
    inString,
    // inside of a string after an escape symbol
    inStringEscaped
};

// returns a string of the input cpp code that has comments removed
std::string stripComments(const std::string& input) {
    std::string result;

    /*
        if we are outside of a comment and we see a slash, we may be starting a comment
        if we saw a slash, check if we entered a single or multi-line comment
        if we see a quote, enter a string
        if we are inside of a string and see a non-escaped quote, exit string
    */

    int i = 0;
    // if true, we are inside of a comment
    CommentState commentState = CommentState::none;
    while(i < input.size()) {
        char c = input[i];

        switch(commentState) {
            case CommentState::none:
                if(c == '/') {
                    commentState = CommentState::noneSlash;
                } else if (c == '"'){
                    commentState = CommentState::inString;
                    result.push_back(c);
                } else {
                    result.push_back(c);
                }
                break;
            case CommentState::noneSlash:
                if(c == '/') {
                    commentState = CommentState::singleLineComment;
                } else if (c == '*'){
                    commentState = CommentState::multiLineComment;
                } else if (c == '"'){
                    commentState = CommentState::inString;
                } else {
                    result.push_back(c);
                    commentState = CommentState::none;
                }
                break;
            case CommentState::singleLineComment:
                if(c == '\n') {
                    result.push_back(c);
                    commentState = CommentState::none;
                }
                break;
            case CommentState::multiLineComment:
                if(c == '*') {
                    commentState = CommentState::multiStar;
                }
                break;
            case CommentState::multiStar:
                if(c == '/') {
                    commentState = CommentState::none;
                } else if(c != '*') {
                    commentState = CommentState::multiLineComment;
                }
                break;
            case CommentState::inString:
                result.push_back(c);
                if(c == '"') {
                    commentState = CommentState::none;
                } else if(c == '\\') {
                    commentState = CommentState::inStringEscaped;
                }
                break;
            case CommentState::inStringEscaped:
                result.push_back(c);
                commentState = CommentState::inString;
                break;
        }
        i++;
    }

    return result;
}

// try to parse the name of an entity, using variable naming rules
// updates out_name to the entity found
// updates i to the char after a successful parse
bool tryParseEntityName(const std::string& input, int& i, std::string& out_name) {
    /*
        variable rules:
        - any uppercase or lowercase chars
        - underscore '_'
        - any digits, except in the start (0th char)
    */
    int resetI = i;
    skipSpace(input, i);
    out_name = "";
    // if true, we are parsing the first char in the sequence
    bool isFirst = true;
    while(i < input.size()) {
        char c = input[i];
        if(isFirst) {
            isFirst = false;
            if(c == '_' || std::isupper(c) || std::islower(c)) {
                out_name.push_back(c);
            } else {
                i = resetI;
                return false;
            }
        } else {
            if(c == '_' || std::isupper(c) || std::islower(c) || std::isdigit(c)) {
                out_name.push_back(c);
            } else {
                // end of symbol, since we're not at the first char we must have a valid entity name
                return true;
            }
        }
        i++;
    }

    // could not find any chars in entity name
    if(isFirst) {
        i = resetI;
        return false;
    } else {
        return true;
    }
}

// tries to parse a known keyword
// updates i to the char after a successful parse
bool tryParseKeyword(const std::string& input, int& i, std::string keyword) {
    int resetI = i;
    std::string entityName;
    if(!tryParseEntityName(input, i, entityName) || entityName != keyword) {
        i = resetI;
        return false;
    } else {
        return true;
    }
}

// parse namespace (like std::)
// filling the namespace string
// updates i to the char after a successful parse
bool tryParseNamespace(const std::string& input, int& i, std::string& out_namespace) {
    int resetI = i;
    std::string namespaceName;
    if(!tryParseEntityName(input, i, namespaceName) || !tryParseNextString(input, i, "::")) {
        i = resetI;
        return false;
    } else {
        out_namespace = namespaceName;
        return true;
    }
}

/*
    internal definition of a variable type
    note that each variable is defined inside of 0 or more namespace (n1::n2:: ...)
    and a simple entity name, as well as a comma-separated list of subtypes
*/
class VarType {
    public:
    std::vector<std::string> namespaces;
    std::string name;
    std::vector<VarType> subtypes;
    // reference type
    bool isRef = false;
    // const type
    bool isConst = false;
    // static type
    bool isStatic = false;
    // levels of indirection (1 = type*, 2 = type**, ...)
    int pointerLevel = 0;

    // return this type as a string
    std::string toString() const {
        return this->toString(true);
    }

    // returns a stringified type
    // if withIndirects is true, add the 'const', 'static', and reference (&) information to the string
    std::string toString(bool withIndirects) const {
        std::string result;
        if(withIndirects) {
            if(isConst) {
                result.append("const ");
            }
            if(isStatic) {
                result.append("static ");
            }
        }
        for(const std::string& ns : namespaces) {
            result.append(ns);
            result.append("::");
        }
        result.append(name);
        bool first = true;
        if(subtypes.size() != 0) {
            result.append("<");
            for(const VarType& subtype : subtypes) {
                if(!first) {
                    result.append(",");
                } else {
                    first = false;
                }
                result.append(subtype.toString());
            }
            result.append(">");
        }
        if(withIndirects && isRef) {
            result.append("&");
        }
        return result;
    }
    
    // returns true if the type matches the type specified by a string
    bool isEqual(std::string otherTypeString) const {
        // try to parse the otherType, and cast it back to a string
        VarType otherType;
        if(!otherType.tryParse(otherTypeString)) {
            return false;
        }
        return this->toString(false) == otherType.toString(false);
    }

    private:

    // fills the current object from a string
    bool tryParse(const std::string& input) {
        int i = 0;
        return tryParse(input, i);
    }
    
    // try to parse static and const keywords
    // updating i afterwards
    bool tryParseStaticConst(const std::string& input, int& i) {
        while(true) {
            if(tryParseKeyword(input, i, "const")) {
                isConst = true;
            } else if(tryParseKeyword(input, i, "static")) {
                isStatic = true;
            } else {
                break;
            }
        }
    }

    public:

    // fills the current object from a string,
    // updating i to the next char position after a successful parse
    bool tryParse(const std::string & input, int& i) {
        /*
            a type is a list of 0 or more namespace (n1::n2:: ...)
            followed by a simple entity name (variable naming rules)
            followed by an optional subtype specified in angle-braces (<>),
            followed by 0 or more stars (*) specifying a pointer or pointer-to-pointer or ...
            and/or followed possibly one ampersand (&) specifying a reference
            and maybe be static and/or const 
            (note that in cpp a function arg cannot be static, but lets not overcomplicate it right now)
            (note: static and const can be defined in any order before the namespaces or after the pointers)
            (note: we should be checking if const or static has been defined twice, but I don't care right now)
            (note: a template subtype cannot be static or const, but I don't care right now)
        */

        static int b = 5;
        const static int* a = &b;
        static std::vector<int> c;

        int resetI = i;

        tryParseStaticConst(input, i);

        std::string namespaceName;
        while(tryParseNamespace(input, i, namespaceName)) {
            namespaces.push_back(namespaceName);
        }

        if(!tryParseEntityName(input, i, name)) {
            i = resetI;
            return false;
        }

        if(tryParseNextChar(input, i, '<')) {
            bool first = true;
            while(i < input.size()) {
                if(!first) {
                    if(!tryParseNextChar(input, i, ',')) {
                        break;
                    }
                } else {
                    first = false;
                }

                VarType subType;
                if(!subType.tryParse(input, i)) {
                    i = resetI;
                    return false;
                } else {
                    subtypes.push_back(subType);
                }
            }

            if(!tryParseNextChar(input, i, '>')) {
                i = resetI;
                return false;
            }
        }

        pointerLevel = 0;
        while(tryParseNextChar(input, i, '*')) {
            pointerLevel++;
        }

        tryParseStaticConst(input, i);

        if(tryParseNextChar(input, i, '&')) {
            isRef = true;
        }

        return true;
    }
};

// a variable definition specified by strings
class VariableDef {
    public:
    VarType varType;
    std::string name;

    std::string toString() const {
        std::string result;
        result.append(varType.toString());
        result.append(" ");
        result.append(name);
        return result;
    }
};

// try to parse a variable definition
// updating the variable type (as a string)
// and updating the variable name
// and updating i to the char after a successful parse
bool tryParseVariableDef(const std::string& input, int& i, VariableDef& out_variableDef) {
    int resetI = i;
    if(!out_variableDef.varType.tryParse(input, i) || !tryParseEntityName(input, i, out_variableDef.name)) {
        i = resetI;
        return false;        
    } else {
        return true;
    }
}

// function definition
class FunctionDef {
    public:
    // return type
    VarType returnType;
    // name of the function
    std::string name;
    // list of arguments
    std::vector<VariableDef> args;
    // the body of the function
    std::string body;
    bool isStatic = false;
    bool isConst = false;

    std::string toString() const {
        std::string result;
        if(isStatic) {
            result.append("static ");
        }
        result.append(returnType.toString());
        result.append(" ");
        result.append(name);
        result.append("(");
        bool first = true;
        for(const VariableDef& arg : args) {
            if(!first) {
                result.append(",");
            } else {
                first = false;
            }
            result.append(arg.toString());
        }
        result.append(")");
        if(isConst) {
            result.append(" const");
        }

        result.append("\n{\n");
        result.append(body);
        result.append("\n}\n");

        return result;
    }

    public:

    // parse function definition from input string, starting at position i
    // updates i to the char after a successful parse
    bool tryParse(const std::string input, int& i) {
        /*
            updates the name of the function
            updates the list of variable definitions after a parse
            updates the body of the function, as a string

            (note: a function cannot be both static and const, but I don't care right now)
            (note: the keyword "const" after a member function definition means
            it cannot alter member variables)
        */
        int resetI = i;

        // optional
        if(tryParseKeyword(input, i, "static")) {
            isStatic = true;
        }

        if (!returnType.tryParse(input, i) || !tryParseEntityName(input, i, name) || !tryParseArgs(input, i)) {
            i = resetI;
            return false;
        }

        // optional 'const' between argument list and body scope
        if(tryParseKeyword(input, i, "const")) {
            isConst = true;
        }

        if(!tryParseScope(input, i)) {
            i = resetI;
            return false;
        }

        return true;
    }

    private:
    // try parsing a function argument list
    // which is a comma-separated list of variables surrounded by braces
    // updates the list of variable definitions after a parse
    // and updates i to the char after a successful parse
    bool tryParseArgs(const std::string& input, int& i) {
        int resetI = i;
        args.clear();

        if(!tryParseNextChar(input, i, '(')) {
            i = resetI;
            return false;
        }

        bool first = true;
        while(i < input.size()) {
            if(first) {
                first = false;
            } else if(!tryParseNextChar(input, i, ',')) {
                break;
            }

            VariableDef variableDef;
            if(!tryParseVariableDef(input, i, variableDef)) {
                break;
            } else {
                args.push_back(variableDef);
            }
        }

        if(!tryParseNextChar(input, i, ')')) {
            args.clear();
            i = resetI;
            return false;
        } else {
            return true;
        }
    }

    private:

    // parse curly-brace escaped scope specifier
    // returning true if successfully parsed
    // updating the scope contents as a string
    // updating i to the char after the successful parse
    bool tryParseScope(const std::string& input, int& i) {
        int resetI = i;
        body = "";

        /*
            note: a scope is specified by curly braces,
            make sure that we aren't inside of a string
            and that curly braces inside of strings are ignored

            try parsing the scope level by counting the curly braces
        */

        if(!tryParseNextChar(input, i, '{')) {
            i = resetI;
            return false;
        }

        // once we reach level 0, we have a successful scope and we can return 
        int level = 1;
        // if true, we are inside of a string
        bool inString = false;
        // if true, we are inside of an escape-sequence inside of a string
        bool inStringEscape = false;

        while(i < input.size()) {
            char c = input[i];
            if(inStringEscape) {
                inStringEscape = false;
            } else if(inString) {
                if(c == '\\') {
                    inStringEscape = true;
                } else if(c == '"') {
                    inString = false;
                }
            } else if(c == '"') {
                inString = true;
            } else if (c == '{') {
                level++;
            } else if(c == '}') {
                level--;
                if(level == 0) {
                    return true;
                }
            }
            body.push_back(c);
            i++;        
        }
        
        // we did not find the end of the current scope
        i = resetI;
        return false;
    }
};

/*
    a class definition
    a class:
    - a name,
    - a list of member functions
    - a list of member variables
*/
class ClassDef {
    /* 
        note, a member may be static, public, const
    */
   static int a;
   const int b = 5;
   static const int c = 6;
   const static int d = 6;
};

/*
    try parsing a class
    sets the name of the class found
    sets it's function definitions (as a string)
    sets i to the char after a successful parse
*/
bool tryParseClass(std::string input, int& i, std::string& out_name, std::vector<FunctionDef>& out_functions) {
    
}

/*
    a function starts with a type definition, a name, argument list in braces,
    and curly braces containing a list of statements
    we will ignore statement parsing for now and just get the function body as a string
*/

/*
    returns a variable type with all refs (&) removed
*/
std::string getTypeWithoutRefs(std::string input) {
    int size = input.size();
    int i = size-1;
    while(i > 0 && (isSpace(input[i]) || input[i] == '&')) {
        i--;
    }
    return input.substr(0, i+1);
}

std::string solutionString = "\
class Solution {\n\
public:\n\
    /*\n\
        create a map of found numbers with their indices\n\
        iterate through each element,\n\
        and for each element, get the associated other number needed\n\
        (remainder = target - nums[i])\n\
        if the needed number exists in the map, return the answer:\n\
        - the current index, and the index of the val in the map\n\
        \n\
    */\n\
    vector<int> twoSum(vector<int>& nums, int target) {\n\
        vector<int> result;\n\
        // val -> index\n\
        map<int, int> foundNums;\n\
        \n\
        for(int i = 0; i < nums.size(); i++) {\n\
            // remainder\n\
            int rem = target - nums[i];\n\
            if(foundNums.find(rem) != foundNums.end()) {\n\
                // we found the needed number, returns its index\n\
                int remIndex = foundNums[rem];\n\
                result.push_back(i);\n\
                result.push_back(remIndex);\n\
                return result;\n\
            } else {\n\
                // else insert the num into the map\n\
                foundNums[nums[i]] = i;\n\
            }\n\
        }\n\
        return result;\n\
    }\n\
};\n\
";

int main() {
    // cout << solutionString << endl;

    // parse input values 
    std::string inStringPart {"nums = [2,7,11,15], target = 9"};

    // parse full input string
    std::string fullInString {"Input: nums = [2,7,11,15], target = 9"};

    // std::string funcName;
    // ArgMap argMap;

    // tryParseSolutionClass(solutionString, i, funcName, argMap);

    cout << stripComments(solutionString) << endl;
    int i = 0;
    std::string varType;
    std::string variableName;

    FunctionDef functionDef;
    std::string input =" std::map<int, std::string> myFunc ( const std :: string hello, std :: \t vector< std::map<int, std::string> > mystrings,int a ) const {int i = 0} ";

    if(functionDef.tryParse(input, i)) {
        cout << functionDef.toString() << endl;
    } else {
        cout << "could not parse" << endl;
    }

    cout << endl << "arguments:" << endl;
    cout << "----------" << endl;
    for(const auto& arg : functionDef.args) {
        cout << arg.toString() << endl;
        cout << "- ";
        if(arg.varType.isEqual("std::string") || arg.varType.isEqual("string")) {
            cout << "recognized string" << endl;
        } else {
            cout << "arg type not recognized" << endl;
        }
    }

    /*
        Example 1:

        Input: nums = [2,7,11,15], target = 9
        Output: [0,1]
        Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
        Example 2:

        Input: nums = [3,2,4], target = 6
        Output: [1,2]
        Example 3:

        Input: nums = [3,3], target = 6
        Output: [0,1]
    */
}