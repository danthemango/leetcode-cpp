// TODO // create a testcase vector, with a sub test-type and a basic subtype
// TODO template <typename TestType, typename SubType>
// TODO class TVector {
// TODO     public:
// TODO     std::vector<SubType> vals;
// TODO 
// TODO     TVector() { }
// TODO 
// TODO     TVector(std::vector<SubType> _vals) {
// TODO         vals = _vals;
// TODO     }
// TODO 
// TODO     std::vector<SubType>& get() {
// TODO         return vals;
// TODO     }
// TODO 
// TODO     // TODO bool operator==(const vector<SubType>& other) {
// TODO     // TODO }
// TODO 
// TODO     bool operator==(const TVector<TestType,SubType>& other) {
// TODO         if(vals.size() != other.size()) {
// TODO             return false;
// TODO         }
// TODO 
// TODO         int i = 0;
// TODO         while(i < vals.size() && i < other.vals.size()) {
// TODO             if(vals[i] != other.vals[i]) {
// TODO                 return false;
// TODO             }
// TODO             ++i;
// TODO         }
// TODO         return true;
// TODO     }
// TODO 
// TODO     bool tryParse(const std::string& input) {
// TODO         return textParse::tryParseVectorInt(input, val);
// TODO     }
// TODO 
// TODO     friend ostream & operator<<(ostream& os, TVector<TestType,SubType>& t) {
// TODO         os << '[';
// TODO         bool first = true;
// TODO         for(const auto& val : t.vals) {
// TODO             if(!first) {
// TODO                 os << ',';
// TODO             } else {
// TODO                 first = false;
// TODO             }
// TODO             os << val;
// TODO         }
// TODO         os << ']';
// TODO     }
// TODO 
// TODO 
// TODO };

