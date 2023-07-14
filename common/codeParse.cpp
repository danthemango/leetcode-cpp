
#include "codeParse.h"
#include "textParse.h"
using namespace textParse;


namespace codeParse {

    // try to parse the name of an entity, using variable naming rules
    // updates out_name to the entity found
    // updates i to the char after a successful parse
    bool tryParseEntityName(const std::string& input, unsigned int& i, std::string& out_name) {
        /*
            variable rules:
            - any uppercase or lowercase chars
            - underscore '_'
            - any digits, except in the start (0th char)
        */
        unsigned int resetI = i;
        textParse::skipSpace(input, i);
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

        unsigned int i = 0;
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

    // parse namespace (like std::)
    // filling the namespace string
    // updates i to the char after a successful parse
    bool tryParseNamespace(const std::string& input, unsigned int& i, std::string& out_namespace) {
        unsigned int resetI = i;
        std::string namespaceName;
        if(!tryParseEntityName(input, i, namespaceName) || !tryParseNextString(input, i, "::")) {
            i = resetI;
            return false;
        } else {
            out_namespace = namespaceName;
            return true;
        }
    }

    // tries to parse a known keyword
    // updates i to the char after a successful parse
    bool tryParseKeyword(const std::string& input, unsigned int& i, std::string keyword) {
        unsigned int resetI = i;
        std::string entityName;
        if(!tryParseEntityName(input, i, entityName) || entityName != keyword) {
            i = resetI;
            return false;
        } else {
            return true;
        }
    }

    // return this type as a string
    std::string VarType::toString() const {
        return this->toString(true);
    }

    // returns a stringified type
    // if withIndirects is true, add the 'const', 'static', and reference (&) information to the type
    std::string VarType::toString(bool withIndirects) const {
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
        for(int i = 0; i < this->pointerLevel; i++) {
            result.push_back('*');
        }
        if(withIndirects && isRef) {
            result.append("&");
        }
        return result;
    }
    
    // returns true if the type matches the type specified by a string
    bool VarType::operator==(const std::string& otherTypeString) const {
        // try to parse the otherType, and cast it back to a string
        VarType otherType;
        if(!otherType.tryParse(otherTypeString)) {
            return false;
        }
        return this->toString(false) == otherType.toString(false);
    }

    bool VarType::operator==(const VarType& otherType) {
        return this->toString(false) == otherType.toString(false);
    }

    // fills the current object from a string
    bool VarType::tryParse(const std::string& input) {
        unsigned int i = 0;
        return tryParse(input, i);
    }
    
    // fills the current object from a string,
    // updating i to the next char position after a successful parse
    bool VarType::tryParse(const std::string & input, unsigned int& i) {
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
            (note: a template subtype cannot be both static and const, but I don't care right now)
        */

        unsigned int resetI = i;

        while(true) {
            if(tryParseKeyword(input, i, "const")) {
                isConst = true;
            } else if(tryParseKeyword(input, i, "static")) {
                isStatic = true;
            } else {
                break;
            }
        }

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

        while(true) {
            if(tryParseKeyword(input, i, "const")) {
                isConst = true;
            } else if(tryParseKeyword(input, i, "static")) {
                isStatic = true;
            } else {
                break;
            }
        }

        if(tryParseNextChar(input, i, '&')) {
            isRef = true;
        }

        return true;
    }

    std::string VariableDef::toString() const {
        std::string result;
        result.append(varType.toString());
        result.append(" ");
        result.append(name);
        return result;
    }

    /*
        try to parse a variable definition
        updating the variable type (as a string)
        and updating the variable name
        and updating i to the char after a successful parse
    */
    bool VariableDef::tryParse(const std::string& input, unsigned int& i) {
        unsigned int resetI = i;
        if(!varType.tryParse(input, i) || !tryParseEntityName(input, i, name)) {
            i = resetI;
            return false;
        }

        std::string stringVal;
        // int intVal;

        return true;
    }

    std::string FunctionDef::toString() const {
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
        result.append(") ");
        if(isConst) {
            result.append(" const");
        }

        result.append("\n{\n");
        result.append(body);
        result.append("\n}\n");

        return result;
    }

    // parse function definition from input string, starting at position i
    // updates i to the char after a successful parse
    bool FunctionDef::tryParse(const std::string input, unsigned int& i) {
        /*
            updates the name of the function
            updates the list of variable definitions after a parse
            updates the body of the function, as a string

            (note: a function cannot be both static and const, but I don't care right now)
            (note: the keyword "const" after a member function definition means
            it cannot alter member variables)
        */
        unsigned int resetI = i;

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

    // try parsing a function argument list
    // which is a comma-separated list of variables surrounded by braces
    // updates the list of variable definitions after a parse
    // and updates i to the char after a successful parse
    bool FunctionDef::tryParseArgs(const std::string& input, unsigned int& i) {
        unsigned int resetI = i;
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
            if(!variableDef.tryParse(input, i)) {
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

    // parse curly-brace escaped scope specifier
    // returning true if successfully parsed
    // updating the scope contents as a string
    // updating i to the char after the successful parse
    bool FunctionDef::tryParseScope(const std::string& input, unsigned int& i) {
        unsigned int resetI = i;
        body = "";

        /*
            note:
            - a scope is specified by curly braces,
            - ensure we aren't inside of a string
            - ensure curly braces inside of strings are ignored
            - ensure quotation marks inside of a string escape sequence are ignored
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
            }
            i++;        
            if(level == 0) {
                return true;
            }
            body.push_back(c);
        }
        
        // we did not find the end of the current scope
        i = resetI;
        return false;
    }

    bool tryParseStringVal(const std::string& input, unsigned int& i, std::string& out_val) {
        unsigned int resetI = i;
        if(!tryParseNextChar(input, i, '"')) {
            i = resetI;
            return false;        
        }

        out_val = "\"";
        while(i < input.size()) {
            if(tryParseChar(input, i, '"')) {
                out_val.push_back('"');
                return true;
            } else if(tryParseString(input, i, "\\\"")) {
                out_val.append("\\\"");
            } else {
                out_val.push_back(input[i]);
                ++i;
            }
        }
        out_val = "";
        i = resetI;
        return false;
    }

    bool tryParseNextStringVal(const std::string& input, unsigned int& i, std::string& out_val) {
        skipSpace(input, i);
        return tryParseStringVal(input, i, out_val);
    }

    bool tryParseVectorInt(const std::string& input, unsigned int& i, std::vector<int>& out_vector) {
        unsigned int resetI = i;
        std::vector<int> result;
        if(!tryParseNextChar(input, i, '[')) {
            i = resetI;
            return false;
        }

        // keep parsing ints until we see the closing brace
        bool first = true;
        while(i < input.size()) {
            if(tryParseNextChar(input, i, ']')) {
                out_vector = result;
                return true;
            }

            if(first) {
                first = false;
            } else if(!tryParseNextChar(input, i, ',')) {
                i = resetI;
                return false;
            }

            int intVal;
            if(tryParseNextInt(input, i, intVal)) {
                result.push_back(intVal);
            } else {
                // invalid value found
                i = resetI;
                return false;
            }

        }

        // error: end of input with no closing brace
        i = resetI;
        return false;
    }

    bool tryParseVectorInt(const std::string& input, std::vector<int>& out_vector) {
        unsigned int i = 0;
        return tryParseVectorInt(input, i, out_vector);
    }

    bool tryParseVectorString(const std::string& input, unsigned int& i, std::vector<std::string>& out_vector) {
        unsigned int resetI = i;
        std::vector<std::string> result;
        if(!tryParseNextChar(input, i, '[')) {
            i = resetI;
            return false;
        }

        // keep parsing ints until we see the closing brace
        bool first = true;
        while(i < input.size()) {
            if(tryParseNextChar(input, i, ']')) {
                out_vector = result;
                return true;
            }

            if(first) {
                first = false;
            } else if(!tryParseNextChar(input, i, ',')) {
                i = resetI;
                return false;
            }

            std::string stringVal;
            if(tryParseNextStringVal(input, i, stringVal)) {
                result.push_back(stringVal);
            } else {
                // invalid value found
                i = resetI;
                return false;
            }

        }

        // error: end of input with no closing brace
        i = resetI;
        return false;
    }

    bool tryParseVectorString(const std::string& input, std::vector<std::string>& out_vector) {
        unsigned int i = 0;
        return tryParseVectorString(input, i, out_vector);
    }

    std::string AssignmentDef::toString() const {
        std::string result;
        result.append(variableDef.toString());
        if(value.size() > 0) {
            result.append(" = ");
            result.append(value);
        }
        return result;
    }

    bool AssignmentDef::tryParse(const std::string& input, unsigned int& i) {
        unsigned int resetI = i;

        if(!variableDef.tryParse(input, i)) {
            i = resetI;
            return false;
        }

        if(tryParseNextChar(input, i, '=')) {
            std::string stringVal;
            int intVal;
            if(tryParseStringVal(input, i, stringVal)) {
                value = stringVal;
            } else if(tryParseNextInt(input, i, intVal)) {
                value = std::to_string(intVal);
            } else {
                // throw exception?
            }
        }

        return true;
    }

    bool MemberVariable::tryParse(const std::string& input, unsigned int& i, AccessLevel _isPublic) {
        isPublic = _isPublic;
        return assignmentDef.tryParse(input,i);
    }

    std::string MemberVariable::toString() {
        return assignmentDef.toString();
    }

    bool MemberFunction::tryParse(const std::string& input, unsigned int& i, AccessLevel _isPublic) {
        isPublic = _isPublic;
        return functionDef.tryParse(input,i);
    }

    std::string MemberFunction::toString() {
        return functionDef.toString();
    }

    /*
        try parsing a class
        sets the name of the class found
        sets it's function definitions (as a string)
        sets i to the char after a successful parse
    */
    bool ClassDef::tryParse(std::string input, unsigned int& i) {
        unsigned int resetI = i;

        /*
            a class is defined with the word 'class', followed by
            the name of a class, curly braces containing member variables and functions,
            followed by a mandatory semicolon
        */

        if(!tryParseKeyword(input, i, "class") || !tryParseEntityName(input, i, name) || !tryParseNextChar(input, i, '{')) {
            i = resetI;
            return false;
        }

        memberFunctions.clear();
        memberVariables.clear();

        AccessLevel accessLevel = AccessLevel::_private;
        // keep parsing any combination of member functions, variables, or 'public:'/'private:' keywords
        // a class may contain 0 or more of these
        while(true) {
            MemberFunction memberFunction;
            MemberVariable memberVariable;

            if(memberFunction.tryParse(input, i, accessLevel)) {
                memberFunctions.push_back(memberFunction);
            } else if(memberVariable.tryParse(input, i, accessLevel) && tryParseNextChar(input, i, ';')) {
                memberVariables.push_back(memberVariable);
            } else if(tryParseNextStrings(input, i, {"public", ":"})) {
                accessLevel = AccessLevel::_public;
            } else if(tryParseNextStrings(input, i, {"private", ":"})) {
                accessLevel = AccessLevel::_private;
            } else {
                break;
            }
        }

        if(!tryParseNextStrings(input, i, {"}", ";"})) {
            i = resetI;
            return false;
        }

        return true;
    }

    // returns all member variables that are public or private
    std::vector<MemberVariable> ClassDef::getMemberVarByAccess(AccessLevel accessLevel) {
        std::vector<MemberVariable> subList;
        for(MemberVariable item : memberVariables) {
            if(item.isPublic == accessLevel) {
                subList.push_back(item);
            }
        }
        return subList;
    }

    std::vector<MemberFunction> ClassDef::getMemberFuncByAccess(AccessLevel accessLevel) {
        std::vector<MemberFunction> subList;
        for(MemberFunction item : memberFunctions) {
            if(item.isPublic == accessLevel) {
                subList.push_back(item);
            }
        }
        return subList;
    }
    
    // returns a string with a specific number of spaces, for indentation
    std::string ClassDef::getIndent(int size) {
        std::string result;
        while(size > 0) {
            result.push_back(' ');
            size--;
        }
        return result;
    }

    std::string ClassDef::toString() {
        std::string result;
        result.append("class ");
        result.append(name);
        result.append(" {\n");


        auto privateFunctions = getMemberFuncByAccess(AccessLevel::_private);
        auto privateVars = getMemberVarByAccess(AccessLevel::_private);
        if(privateFunctions.size() > 0 || privateVars.size() > 0) {
            result.append(getIndent(4));
            result.append("private:\n");
        }
        for(auto func : privateFunctions) {
            result.append(getIndent(4));
            result.append(func.toString());
            result.append("\n");
        }

        for(auto var : privateVars) {
            result.append(getIndent(4));
            result.append(var.toString());
            result.append(";\n");
        }

        auto publicFunctions = getMemberFuncByAccess(AccessLevel::_public);
        auto publicVars = getMemberVarByAccess(AccessLevel::_public);
        if(publicFunctions.size() > 0 || publicVars.size() > 0) {
            result.append(getIndent(4));
            result.append("public:\n");
        }
        for(auto func : publicFunctions) {
            result.append(getIndent(4));
            result.append(func.toString());
            result.append("\n");
        }

        for(auto var : publicVars) {
            result.append(getIndent(4));
            result.append(var.toString());
            result.append(";\n");
        }
        result.append("};\n");
        return result;
    }
}
