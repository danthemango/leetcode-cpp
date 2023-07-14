/* vector<vector<string>> */
#ifndef TVVSTRING_H
#define TVVSTRING_H

#include <string>
#include <vector>

class TVVString  {
    public:
    std::vector<std::vector<std::string>> val;

    TVVString();

    TVVString(std::vector<std::vector<std::string>> _val);

    std::vector<std::vector<std::string>>& get();

    bool operator==(const std::vector<std::vector<std::string>>& other);

    bool operator==(const TVVString& other);

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVVString& t);
};

#endif // TVVSTRING_H