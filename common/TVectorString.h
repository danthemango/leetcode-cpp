/* vector<string> wrapper */
class TVectorString {
    public:
    std::vector<std::string> val;
    TVectorString();
    TVectorString(std::vector<std::string> _val);

    bool operator==(TVectorString& other);

    std::vector<std::string>& get();

    // returns true if there was a quote-delimited string value in input at pos i
    // updating i to the char after a successful parse
    // updating out_val with the string contents
    bool tryParseStringValue(const std::string& input, int& i, std::string& out_val);

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVectorString& t);
};

