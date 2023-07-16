#include <string>
#include <iostream>

// nullable result type
enum class NRType {
    nrNull,
    nrBool,
    nrInt,
    nrString
};

// a nullable value
class NullableResult {
    public:
    NRType type;
    bool bVal;
    int iVal;
    std::string sVal;

    // returns a null value result
    NullableResult();
    // returns a boolean value result
    NullableResult(bool _bVal);
    // returns an int value result
    NullableResult(int iVal);
    // returns a string value result
    NullableResult(std::string val);

    // returns a null value result
    static NullableResult getNull();
    // returns true if this result could be parsed from input, updating i to the char after a successful parse
    bool tryParse(const std::string& input, unsigned int& i);
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, NullableResult& nr);
    bool operator==(const NullableResult& other) const;
    bool operator!=(const NullableResult& other) const;
};
