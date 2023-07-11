#ifndef CODEPARSE_H
#define CODEPARSE_H

#include <string>
#include <vector>

/* codeParse.h responsible for simple C++ code parsing */

namespace codeParse {

    // try to parse the name of an entity, using variable naming rules
    // updates out_name to the entity found
    // updates i to the char after a successful parse
    bool tryParseEntityName(const std::string& input, int& i, std::string& out_name);

    // returns a string of the input cpp code that has comments removed
    std::string stripComments(const std::string& input);

    // parse namespace (like std::)
    // filling the namespace string
    // updates i to the char after a successful parse
    bool tryParseNamespace(const std::string& input, int& i, std::string& out_namespace);

    // tries to parse a known keyword
    // updates i to the char after a successful parse
    bool tryParseKeyword(const std::string& input, int& i, std::string keyword);

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
        std::string toString() const;

        // returns a stringified type
        // if withIndirects is true, add the 'const', 'static', and reference (&) information to the type
        std::string toString(bool withIndirects) const;
        
        // returns true if the type matches the type specified by a string
        bool operator==(const std::string& otherTypeString) const;

        bool operator==(const VarType& otherType);

        // fills the current object from a string
        bool tryParse(const std::string& input);
        
        // fills the current object from a string,
        // updating i to the next char position after a successful parse
        bool tryParse(const std::string & input, int& i);
    };

    // a variable definition specified by strings
    class VariableDef {
        public:
        VarType varType;
        std::string name;

        std::string toString() const;

        /*
            try to parse a variable definition
            updating the variable type (as a string)
            and updating the variable name
            and updating i to the char after a successful parse
        */
        bool tryParse(const std::string& input, int& i);
    };

    /*
        a function starts with a type definition, a name, argument list in braces,
        and curly braces containing a list of statements
        we will ignore statement parsing for now and just get the function body as a string
    */
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

        std::string toString() const;

        public:

        // parse function definition from input string, starting at position i
        // updates i to the char after a successful parse
        bool tryParse(const std::string input, int& i);

        private:

        // try parsing a function argument list
        // which is a comma-separated list of variables surrounded by braces
        // updates the list of variable definitions after a parse
        // and updates i to the char after a successful parse
        bool tryParseArgs(const std::string& input, int& i);

        private:

        // parse curly-brace escaped scope specifier
        // returning true if successfully parsed
        // updating the scope contents as a string
        // updating i to the char after the successful parse
        bool tryParseScope(const std::string& input, int& i);
    };

    bool tryParseStringVal(const std::string& input, int& i, std::string& out_val);

    /* a variable assignment */
    class AssignmentDef {
        public:
        VariableDef variableDef;
        std::string value;

        std::string toString() const;

        bool tryParse(const std::string& input, int& i);
    };

    /* for private/public members*/
    enum class AccessLevel {
        _public,
        _private
    };

    /*
        member variable inside of a class
    */
    class MemberVariable {
        public:
        AccessLevel isPublic = AccessLevel::_private;
        AssignmentDef assignmentDef;

        bool tryParse(const std::string& input, int& i, AccessLevel _isPublic);

        std::string toString();
    };

    /*
        member function inside of a class
    */
    class MemberFunction {
        public:
        AccessLevel isPublic = AccessLevel::_private;
        FunctionDef functionDef;

        bool tryParse(const std::string& input, int& i, AccessLevel _isPublic);

        std::string toString();
    };

    /*
        a class definition
        a class:
        - a name,
        - a list of member functions
        - a list of member variables
    */
    class ClassDef {
        public:
        std::string name;
        // a list of member functions
        std::vector<MemberFunction> memberFunctions;
        // a list of member variables
        std::vector<MemberVariable> memberVariables;

        /*
            try parsing a class
            sets the name of the class found
            sets it's function definitions (as a string)
            sets i to the char after a successful parse
        */
        bool tryParse(std::string input, int& i);

        // returns all member variables that are public or private
        std::vector<MemberVariable> getMemberVarByAccess(AccessLevel accessLevel);

        std::vector<MemberFunction> getMemberFuncByAccess(AccessLevel accessLevel);
        
        // returns a string with a specific number of spaces, for indentation
        std::string getIndent(int size);

        std::string toString();
    };

}

#endif // CODEPARSE_H
