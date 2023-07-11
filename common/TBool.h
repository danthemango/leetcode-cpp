#ifndef TBOOL_H
#define TBOOL_H

#include <iostream>

/* testtype boolean handler */
class TBool {
    public:
    bool val;

    TBool();

    TBool(bool _val);

    bool& get();

    bool operator==(const bool& other);

    bool operator==(const TBool& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TBool& t);
};

#endif // TBOOL_H
