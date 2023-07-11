/* vector<vector<int>> */
#ifndef TVVINT_H
#define TVVINT_H
#include <iostream>
#include <vector>

/* testcase vector type */
class TVVInt {
    public:
    std::vector<std::vector<int>> val;

    TVVInt();

    TVVInt(std::vector<std::vector<int>> _val);

    std::vector<std::vector<int>>& get();

    bool operator==(const std::vector<std::vector<int>>& other);

    bool operator==(const TVVInt& other);

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVVInt& t);
};

#endif // TVVINT_H
