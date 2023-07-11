#ifndef TVECTORINT_H
#define TVECTORINT_H
#include <iostream>
#include <vector>

/* testcase vector type */
class TVectorInt {
    public:
    std::vector<int> val;

    TVectorInt();

    TVectorInt(std::vector<int> _val);

    std::vector<int>& get();

    bool operator==(const std::vector<int>& other);

    bool operator==(const TVectorInt& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TVectorInt& t);
};

#endif // TVECTORINT_H
