
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class HTMLNode
{
private:
    std::string myTag;
    std::string myValue;
    std::vector<HTMLNode> myChildren;
    std::unordered_map<std::string, std::string> myProps;

public:
    HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::unordered_map<std::string, std::string> theProps);

    void toHTML();
    std::string propsToHTML();
};
