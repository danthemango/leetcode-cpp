#include "../../common/common.h"
using namespace std;

namespace XMLParse {

    /* returns a string with the indentation level expected */
    std::string getLevelIndent(int level) {
        std::string result;
        const static int numSpaces = 4;
        while(level > 0) {
            for(int i = 0; i < numSpaces; i++) {
                result.push_back(' ');
            }
            --level;
        }
        return result;
    }

    /*
        returns true if we have a symbol which may be used in
        an xml tag or attribute name. (alphanumeric or dash)
        updating i to the next char on success
    */
    bool isTagSymbol(const char& c) {
        return std::isupper(c) || std::islower(c) || c == '-';
    }

    /*
        returns true if parsing an xml keyword was possible
        an xml keyword is:
        - must have 1 or more chars
        - the name of a tag or attribute
        - case insensitive (will be cast as lowercase on parse)
        - may be have alphanumeric or dash characters
    */
    bool tryParseKeyname(const std::string& input, int& i, std::string& out_keyname) {
        skipSpace(input, i);
        if(i >= input.size()) {
            return false;
        }

        std::string keyname;
        int resetI = i;
        while(i < input.size() && isTagSymbol(input[i])) {
            char c = input[i];
            if(std::isupper(input[i])) {
                c = std::tolower(input[i]);
            }
            keyname.push_back(c);
            i++;
        }

        if(keyname.size() > 0) {
            out_keyname = keyname;
            return true;
        } else {
            i = resetI;
            return false;
        }
    }

    /*
        returns true if we have successfully parsed an attribute value
        which is a single-quote or double-quote delimited string
        on a successful parse:
        updates i to the end of the string
        updates out_content to the end of the string
    */
    bool tryParseAttributeValue(const std::string& input, int& i, std::string& out_content) {
        int resetI = i;
        // specify the delimiter charactr (single or double quote)
        char delim;
        if(tryParseNextChar(input, i, '"')) {
            delim = '"';
        } else if(tryParseNextChar(input, i, '\'')) {
            delim = '\'';
        } else {
            return false;
        }

        std::string content;
        while(i < input.size()) {
            // successful parse if delim char found
            if(tryParseNextChar(input, i, delim)) {
                out_content = content;
                return true;
            }

            content.push_back(input[i]);
            i++;
        }

        // delim char never found before the end of input, fail
        i = resetI;
        return false;
    }

    /*
        returns true if we find an attribute setting
        which may be an atttribute name, and optionally 
        an attribute value in the format of:
            name="value"
        on successful parse:
        - updates out_name
        - update out_val
        - updates i to the char after the attribute
        updating the name and value on successful parse
        updates i on successful parse

        note: any quotes in an attribute value must be escaped
        - single quotes (') like &quot;
        - double quotes (") like &quot;
    */
    bool tryParseAttribute(const std::string& input, int& i, std::string& out_name, std::string& out_val) {
        int resetI = i;
        std::string name;
        std::string val;
        if(!tryParseKeyname(input, i, name)) {
            i = resetI;
            return false;
        }
        cout << "the name is " << name << endl;
        out_name = name;
        if(!tryParseNextChar(input, i, '=') || !tryParseAttributeValue(input, i, val)) {
            out_val = "";
            return true;
        }
        out_val = val;
        return true;
    }

    /*
    */
    class XMLNode {
        public:
        std::string name;
        std::map<std::string, std::string> attributes;
        std::vector<XMLNode> children;
        // any text content in this node
        std::string innerText = "";
        // true if this is a self-closing tag
        bool isSelfClosing = false;

        void clear() {
            isSelfClosing = false;
            innerText = "";
            children.clear();
            attributes.clear();
            name = "";
        }

        // sets an attribute
        void setAttribute(std::string name, std::string val) {
            attributes[name] = val;
        }

        std::string toString(int level) const {
            if(innerText != "") {
                std::string result;
                result.append(getLevelIndent(level));
                result.append(innerText);
                return result;
            }

            std::string result;
            result.append(getLevelIndent(level));
            result.push_back('<');
            result.append(name);
            for(const std::pair<string, string>& atPair : attributes) {
                const std::string& name = atPair.first;
                const std::string& val = atPair.second;
                result.push_back(' ');
                result.append(name);
                if(val.size() != 0) {
                    result.push_back('=');
                    result.push_back('"');
                    result.append(val);
                    result.push_back('"');
                }
            }

            if(isSelfClosing) {
                result.push_back('/');
                result.push_back('>');
                return result;
            } else {
                result.push_back('>');
            }

            for(const auto& child : children) {
                result.push_back('\n');
                result.append(child.toString(level+1));
            }

            result.push_back('\n');
            result.append(getLevelIndent(level));
            result.push_back('<');
            result.push_back('/');
            result.append(name);
            result.push_back('>');

            return result;
        }

        std::string toString() const {
            return toString(0);
        }
    };

    /*
        returns true if on parsing a self-closing tag,
        updating tag name and attributes on successful parse
        updating i to the char after the opening tag
    */
    bool tryParseOpenTag(const std::string& input, int& i, XMLNode& out_tag) {
        int resetI = i;
        if(!tryParseNextChar(input, i, '<') || !tryParseKeyname(input, i, out_tag.name)) {
            i = resetI;
            return false;
        }

        std::string name;
        std::string val;
        while(tryParseAttribute(input, i, name, val)) {
            out_tag.attributes[name] = val;
        }

        if(tryParseNextChar(input, i, '/') && tryParseNextChar(input, i, '>')) {
            out_tag.isSelfClosing = true;
            return true;
        } else if(tryParseNextChar(input, i, '>')) {
            out_tag.isSelfClosing = false;
            return true;
        }
        return false;
    }

    /*
        returns true on a successfully parsed xml closing tag
        updates i to the the char after a successful parse
    */
    bool tryParseClosingTag(const std::string& input, int& i, const std::string& name) {
        int resetI = i;
        if(!tryParseNextChar(input, i, '<')
            || !tryParseNextChar(input, i, '/')
            || !tryParseNextString(input, i, name)
            || !tryParseNextChar(input, i, '>')) {
            i = resetI;
            return false;
        } else {
            return true;
        }
    }

    /*
        tries to parse any non-whitespace values until the 
        next opening or closing xml node
        updating i to the char after successful parse
        returning i if any chars found
    */
    bool tryParseTextNode(const std::string& input, int& i, XMLNode& out_node) {
        std::string text;
        std::string spaceCache;
        int resetI = i;
        bool hasSpace = false;
        skipSpace(input, i);
        while(i < input.size() && input[i] != '<') {
            if(skipSpace(input, i)) {
                hasSpace = true;
                continue;
            }

            if(hasSpace) {
                text.push_back(' ');
                hasSpace = false;
            }

            text.push_back(input[i]);
            ++i;
        }

        if(text.size() > 0) {
            out_node.innerText = text;
            return true;
        } else {
            i = resetI;
            return false;
        }
    }

    /*
        returns true if parsing an XMLNode was possible
        updates i to the end of a successful parse

        a tag and a subtag may look like this:
        <tagname attr1="val1" attr2="val2"> text1 <subtag1/> text2 <subtag2> </subtag2> </tagname>
        note: a closing tag or slash (</>) is always required
    */
    bool tryParseNode(const std::string& input, int& i, XMLNode& out_node) {
        /*
            if there is no opening tag, then accept any non-whitespace text
                until the end of input or the next '<' found, whatever comes first,
                updating i.
                Then set this with innerText and don't bother filling any other entries.
            else if there's a self-closing tag, parse it and return
            else
                parse it, and continue parsing children until we find a closing tag
            then discard any whitespace at the end of input
        */
        int resetI = i;

        if(tryParseTextNode(input, i, out_node)) {
            return true;
        } else if(tryParseOpenTag(input, i, out_node)) {
            if(out_node.isSelfClosing) {
                return true;
            } else {

                XMLNode child;
                while(tryParseNode(input, i, child)) {
                    out_node.children.push_back(child);
                }

                if(!tryParseClosingTag(input, i, out_node.name)) {
                    i = resetI;
                    return false;
                } else {
                    return true;
                }
            }
        } else {
            i = resetI;
            return false;
        }
    }

    /*
        fills a list of xml nodes
    */
    std::vector<XMLNode> getNodes(const std::string& input, int& i) {
        std::vector<XMLNode> nodes;
        // ensure we have non-whitespace values in the string
        skipSpace(input, i);
        while(true) {
            XMLNode node;
            if(tryParseNode(input, i, node)) {
                nodes.push_back(node);
            } else {
                return nodes;
            }
        }
    }
}

using namespace XMLParse;

int main() {
    std::string xmlTagString = " <article> <p class='main' id='hello'> just some text here </p> </article> ";

    cout << xmlTagString << endl;
    std::string name, val;
    std::string attributeString = "myname=\"the joker\"";
    int i = 0;

    std::vector<XMLNode> xmlNodes = XMLParse::getNodes(xmlTagString, i);

    for(const auto& xmlNode : xmlNodes){
        cout << "tag: " << endl << xmlNode.toString() << endl;
    }
}
