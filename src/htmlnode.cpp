
#include "htmlnode.hpp"

HTMLNode::HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::string> theProps)
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

std::string HTMLNode::propsToHTML()
{
    std::stringstream output;

    for (const auto& [key, value]: myProps)
    {
        output << " " << key << "=\"" << value << "\"";
    }

    return output.str();
}

std::string HTMLNode::stringRepresentation()
{
    std::stringstream output;

    output << "tag = " << myTag << "\n" << "value = " << myValue
        << "\n" << "children = ";

    return output.str();
}

void HTMLNode::setTag(std::string theTag)
{
    myTag = theTag;
}

void HTMLNode::setValue(std::string theValue)
{
    myValue = theValue;
}

void HTMLNode::setProps(std::map<std::string, std::string> theProps)
{
    myProps = theProps;
}
