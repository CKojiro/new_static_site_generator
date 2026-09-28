
#include "htmlnode.hpp"

HTMLNode::HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::unordered_map<std::string, std::string> theProps)
{
    myTag = theTag;
    myValue = theValue;
    myChildren = theChildren;
    myProps = theProps;
}

void HTMLNode::toHTML()
{
    throw std::logic_error("Functionality not implemented!");
}

std::string propsToHTML()
{
    std::stringstream output;

    

    return output.str();
}
