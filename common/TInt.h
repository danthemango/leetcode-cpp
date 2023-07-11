#pragma once
#ifndef TINT_H
#define TINT_H
#include <iostream>
#include <string>
#include <ostream>

/* testcase int type */
class TInt {
    public:
    int val;

    TInt();
    TInt(int _val);

    int& get();

    bool tryParse(const std::string& input);

    bool operator==(const TInt& other);

    friend std::ostream & operator<<(std::ostream& os, TInt& t);
};

#endif // TINT_H
