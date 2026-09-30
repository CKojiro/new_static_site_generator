
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>

class HTMLNode
{
private:
    std::string myTag;
    std::string myValue;
    std::vector<HTMLNode> myChildren;
    std::map<std::string, std::string> myProps;

public:
    HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::string> theProps);

    virtual void toHTML();
    std::string propsToHTML();
    std::string stringRepresentation();
};
