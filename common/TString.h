#ifndef TSTRING_H
#define TSTRING_H

#include <iostream>

/* testtype string type handler */
class TString {
    public:
    std::string val;

    TString();

    TString(bool _val);

    std::string& get();

    bool operator==(const std::string& other);

    bool operator==(const TString& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TString& t);
};

#endif // TSTRING_H
