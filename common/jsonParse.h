#ifndef JSONPARSE_H
#define JSONPARSE_H

/*
    some lovely graphs may be viewed at:
    https://www.json.org/json-en.html
*/

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include "inputParse.h"

namespace js {

    /* js headers */

    // returns indentation level spaces
    std::string getIndent(int level);

    /* a json value */
    class JValue {
        public:

        virtual std::string toString() const = 0;

        virtual std::string toString(bool toIndent, int level) const = 0;

        virtual std::string getType() const = 0;

        static std::shared_ptr<JValue> tryParse(InputParser& ip);

        static std::shared_ptr<JValue> tryParse(std::string input);

        friend std::ostream & operator<<(std::ostream& os, std::shared_ptr<JValue>& jValue);
    };

    /* string as json value */
    class JString : public JValue {
        private:
        JString();
        
        public:
        std::string content;

        JString(std::string _content);

        std::string getType() const;

        std::string get() const;

        virtual std::string toString() const;

        virtual std::string toString(bool toIndent, int level) const;

        enum class states {
            nostring, // before or after a string sequence
            instring, // inside of a string
            incontrol // inside of a control sequence
        };

        /*
            returns a JString object if input was successfully parsed,
            else returns null
        */
        static std::shared_ptr<JString> tryParse(InputParser& ip);
    };

    /* number value */
    class JNumber : public JValue {
        public:
        double content;

        JNumber(double _content);

        std::string getType() const;

        double get() const;

        virtual std::string toString() const;

        virtual std::string toString(bool toIndent, int level) const;

        /* returns a json number */
        static std::shared_ptr<JNumber> tryParse(InputParser& ip);
    };

    /* boolean value */
    class JBoolean : public JValue {
        private: 
        JBoolean();

        public:
        bool content;
        JBoolean(bool _content);

        std::string getType() const;

        bool get() const;

        virtual std::string toString() const;

        virtual std::string toString(bool toIndent, int level) const;

        static std::shared_ptr<JBoolean> tryParse(InputParser& ip);
    };

    /* null value */
    class JNull : public JValue {
        public:
        JNull();

        std::string getType() const;

        virtual std::string toString() const;

        virtual std::string toString(bool toIndent, int level) const;

        static std::shared_ptr<JNull> tryParse(InputParser& ip);
    };

    /* a json array */
    class JArray : public JValue {
        public:
        std::vector<std::shared_ptr<JValue>> content;

        std::string getType() const;

        std::shared_ptr<JValue> get(int i);

        int size();

        void push_back(std::shared_ptr<JValue> value);

        void push_back(std::string value);

        void push_back(double value);

        // if toIndent is true, we will pretty-print indented json
        virtual std::string toString(bool toIndent, int level) const;

        virtual std::string toString() const;


        static std::shared_ptr<JArray> tryParse(InputParser& ip);
    };

    /* a json object */
    class JObject : public JValue {
        public:
        std::map<std::string, std::shared_ptr<JValue>> content;

        std::string getType() const;

        void set(std::string key, std::shared_ptr<JValue> value);

        void set(std::string key, std::string val);

        bool has(std::string key);

        std::shared_ptr<JValue> get(std::string key);

        virtual std::string toString(bool toIndent, int level) const;

        virtual std::string toString() const;

        static std::shared_ptr<JObject> tryParse(InputParser& ip);
        static std::shared_ptr<JObject> tryParse(std::string input);
    };

    /* return an abstract pointer to child-instance pointer, if possible */
    std::shared_ptr<JString> toJString(const std::shared_ptr<JValue>& jValue);
    std::shared_ptr<JNumber> toJNumber(const std::shared_ptr<JValue>& jValue);
    std::shared_ptr<JBoolean> toJBoolean(const std::shared_ptr<JValue>& jValue);
    std::shared_ptr<JNull> toJNull(const std::shared_ptr<JValue>& jValue);
    std::shared_ptr<JArray> toJArray(const std::shared_ptr<JValue>& jValue);
    std::shared_ptr<JObject> toJObject(const std::shared_ptr<JValue>& jValue);

}

#endif // JSONPARSE_H
