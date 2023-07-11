#include "jsonParse.h"
#include "textParse.h"
#include "inputParse.h"
#include "codeParse.h"

namespace js {

    // returns indentation level spaces
    std::string getIndent(int level) {
        ++level;
        std::string result;
        while(level > 0) {
            for(int i = 0; i < 4; i++) {
                result.push_back(' ');
            }
            --level;
        }
        return result;
    }

    /* JValue */
    std::shared_ptr<JValue> JValue::tryParse(InputParser& ip) {
        std::shared_ptr<JValue> result;

        // try parsing the input as one of the value subtypes
        if((result = JString::tryParse(ip)) != nullptr) {
            return result;
        } else if((result = JNull::tryParse(ip)) != nullptr) {
            return result;
        } else if((result = JBoolean::tryParse(ip)) != nullptr) {
            return result;
        } else if((result = JNumber::tryParse(ip)) != nullptr) {
            return result;
        } else if((result = JArray::tryParse(ip)) != nullptr) {
            return result;
        } else if((result = JObject::tryParse(ip)) != nullptr) {
            return result;
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<JValue> JValue::tryParse(std::string input) {
        InputParser ip(input);
        return JValue::tryParse(ip);
    }

    std::ostream & operator<<(std::ostream& os, std::shared_ptr<JValue>& jValue) {
        os << jValue->toString();
        return os;
    }

    /* JString */
    JString::JString() { }

    JString::JString(std::string _content) : content(_content) { }

    std::string JString::getType() const {
        return "string";
    }

    std::string JString::get() const {
        return content;
    }

    std::string JString::toString() const {
        std::string result;
        result.push_back('"');
        result.append(content);
        result.push_back('"');
        return result;
    }

    std::string JString::toString(bool toIndent, int level) const {
        return this->toString();
    }

    /* JNumber */
    JNumber::JNumber(double _content) {
        content = _content;
    }

    std::string JNumber::getType() const {
        return "number";
    }

    double JNumber::get() const {
        return content;
    }

    std::string JNumber::toString() const {
        return std::to_string(content);
    }

    std::string JNumber::toString(bool toIndent, int level) const {
        return this->toString();
    }

    /* returns a json number */
    std::shared_ptr<JNumber> JNumber::tryParse(InputParser& ip) {
        /* a json number may be formatted like an int or a double */
        /*
            it is formatted as:
            - an optional negative sign
            - followed by either:
                - a 0
                - OR followed by any starting digit 1 through 9
                    - followed by any number of digits afterward
            - followed by an optional fractional part
                - a period
                - followed by any number of digits afterward
            - followed by an exponential part
                - an 'e' or 'E'
                - an optional '+' or '-'
                - followed by any number of digits
        */
        ip.skipSpace();
        int sign = 1;
        int wholePart;
        int _i = ip.pos();
        if(ip.tryParseNextChar('-')) {
            sign = -1;
        }
        if(ip.tryParseChar('0')) {
            wholePart = 0;
        } else {
            char c = ip.get();
            if('1' <= c && c <= '9') {
                wholePart = c - '0';
            } else {
                ip.recover(_i);
                return nullptr;
            }
            ++ip;
            while(true) {
                char c = ip.get();
                if(c < '0' || c > '9') {
                    break;
                } else {
                    wholePart *= 10;
                    wholePart += c - '0';
                    ++ip;
                }
            }
        }
        // TODO parse the rest
        return std::shared_ptr<JNumber> (new JNumber(sign * wholePart));
    }

    /* JBoolean */
    JBoolean::JBoolean() { }
    JBoolean::JBoolean(bool _content) : content(_content) { }

    std::string JBoolean::getType() const {
        return "boolean";
    }

    bool JBoolean::get() const { 
        return content;
    }

    std::string JBoolean::toString() const {
        if(content) {
            return "true";
        } else {
            return "false";
        }
    }

    std::string JBoolean::toString(bool toIndent, int level) const {
        return this->toString();
    }

    std::shared_ptr<JBoolean> JBoolean::tryParse(InputParser& ip) {
        auto result = std::shared_ptr<JBoolean>(new JBoolean());
        if(ip.tryParseNextString("true")) {
            result->content = true;
            return result;
        } else if(ip.tryParseNextString("false")) {
            result->content = false;
            return result;
        } else {
            return nullptr;
        }
    }

    /* JNull */
    JNull::JNull() { }

    std::string JNull::getType() const {
        return "null";
    }

    std::string JNull::toString() const {
        return "null";
    }

    std::string JNull::toString(bool toIndent, int level) const {
        return this->toString();
    }

    std::shared_ptr<JNull> JNull::tryParse(InputParser& ip) {
        auto result = std::shared_ptr<JNull>(new JNull());
        if(ip.tryParseNextString("null")) {
            return result;
        } else {
            return nullptr;
        }
    }

    /* JArray */
    std::string JArray::getType() const {
        return "array";
    }

    std::shared_ptr<JValue> JArray::get(int i) {
        return content[i];
    }

    int JArray::size() {
        return content.size();
    }

    void JArray::push_back(std::shared_ptr<JValue> value) {
        content.push_back(value);
    }

    void JArray::push_back(std::string value) {
        content.push_back(std::shared_ptr<JString>(new JString{value}));
    }

    void JArray::push_back(double value) {
        content.push_back(std::shared_ptr<JNumber>(new JNumber{value}));
    }

    // if toIndent is true, we will pretty-print indented json
    std::string JArray::toString(bool toIndent, int level) const {
        std::string result;
        result.append("[");
        if(toIndent) {
            result.push_back('\n');
        }
        bool first = true;
        for(const std::shared_ptr<JValue>& jValue : this->content) {
            if(!first) {
                result.push_back(',');
                if(toIndent) {
                    result.push_back('\n');
                }
            } else {
                first = false;
            }
            if(toIndent) {
                result.append(getIndent(level));
            }
            result.append(jValue->toString(toIndent, level+1));
        }
        if(toIndent) {
            result.push_back('\n');
            result.append(getIndent(level-1));
        }
        result.append("]");
        return result;
    }

    std::string JArray::toString() const {
        return this->toString(true, 0);
    }

    /* JObject */
    std::string JObject::getType() const {
        return "object";
    }

    void JObject::set(std::string key, std::shared_ptr<JValue> value) {
        content[key] = value;
    }

    void JObject::set(std::string key, std::string val) {
        content[key] = std::shared_ptr<JString>(new JString(val));
    }

    bool JObject::has(std::string key) {
        return content.find(key) != content.end();
    }

    std::shared_ptr<JValue> JObject::get(std::string key) {
        if(!has(key)) {
            return nullptr;
        } else {
            return content[key];
        }
    }

    std::string JObject::toString(bool toIndent, int level) const {
        std::string result;
        result.push_back('{');
        if(toIndent) {
            result.push_back('\n');
        }
        bool first = true;
        for(const auto& pair : content) {
            if(!first) {
                result.push_back(',');
                if(toIndent) {
                    result.push_back('\n');
                }
            } else { 
                first = false;
            }
            const auto& key = pair.first;
            const auto& value = pair.second;
            if(toIndent) {
                result.append(getIndent(level));
            }
            result.push_back('"');
            result.append(key);
            result.append("\":");
            if(toIndent) {
                result.push_back(' ');
            }
            result.append(value->toString(toIndent, level+1));
        }
        if(toIndent) {
            result.push_back('\n');
        }
        if(toIndent) {
            result.append(getIndent(level-1));
        }
        result.push_back('}');
        return result;
    }

    std::string JObject::toString() const {
        return this->toString(true, 0);
    }

    /* end */

    // returns a JString object if input was successfully parsed,
    // else returns null
    std::shared_ptr<JString> JString::tryParse(InputParser& ip) {
        int _i = ip.pos();
        if(!ip.tryParseNextChar('"')) {
            ip.recover(_i);
            return nullptr;
        }

        auto result = std::shared_ptr<JString>(new JString());
        result->content = "";
        while(!ip.atEnd()) {
            if(ip.tryParseChar('"')) {
                return result;
            } else if(ip.tryParseString("\\\"")) {
                result->content.append("\\\"");
            } else {
                result->content.push_back(ip.get());
                ++ip;
            }
        }
        result->content = "";
        ip.recover(_i);
        return nullptr;
    }

    /* JArray */
    std::shared_ptr<JArray> JArray::tryParse(InputParser& ip) {
        auto result = std::shared_ptr<JArray>(new JArray());
        int _i = ip.pos();
        if(!ip.tryParseNextChar('[')) {
            ip.recover(_i);
            return nullptr;
        }

        std::shared_ptr<JValue> subValue;
        while((subValue = JValue::tryParse(ip)) != nullptr) {
            result->push_back(subValue);
            if(!ip.tryParseNextChar(',')) {
                break;
            }
        }

        if(!ip.tryParseNextChar(']')) {
            ip.recover(_i);
            return nullptr;
        }
        return result;
    }

    /* JObject */
    std::shared_ptr<JObject> JObject::tryParse(std::string input) {
        InputParser ip(input);
        return tryParse(ip);
    }

    std::shared_ptr<JObject> JObject::tryParse(InputParser& ip) {
        auto result = std::shared_ptr<JObject>(new JObject());
        int _i = ip.pos();
        if(!ip.tryParseNextChar('{')) {
            ip.recover(_i);
            return nullptr;
        }

        std::shared_ptr<JString> key;
        std::shared_ptr<JValue> value;
        // keep fetching key-value pairs separated by colons
        while((key = JString::tryParse(ip)) != nullptr && ip.tryParseNextChar(':') && (value = JValue::tryParse(ip)) != nullptr) {
            result->set(key->content, value);
            if(!ip.tryParseNextChar(',')) {
                break;
            }
        }

        if(!ip.tryParseNextChar('}')) {
            ip.recover(_i);
            return nullptr;
        }
        return result;
    }

    std::shared_ptr<JString> toJString(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JString>(jValue);
    }
    std::shared_ptr<JNumber> toJNumber(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JNumber>(jValue);
    }
    std::shared_ptr<JBoolean> toJBoolean(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JBoolean>(jValue);
    }
    std::shared_ptr<JNull> toJNull(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JNull>(jValue);
    }
    std::shared_ptr<JArray> toJArray(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JArray>(jValue);
    }
    std::shared_ptr<JObject> toJObject(const std::shared_ptr<JValue>& jValue) {
        return std::static_pointer_cast<js::JObject>(jValue);
    }

}
