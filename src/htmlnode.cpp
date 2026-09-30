
#include "htmlnode.hpp"

HTMLNode::HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::pair<std::string, std::string>> theProps)
{
    myTag = theTag;
    myValue = theValue;
    myChildren = theChildren;
    myProps = theProps;
}

std::string HTMLNode::toHTML()
{
    throw std::logic_error("Functionality not implemented!");

    return "";
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

std::string HTMLNode::getTag()
{
    return this->myTag;
}

std::string HTMLNode::getValue()
{
    return this->myValue;
}

std::map<std::string, std::pair<std::string, std::string>> HTMLNode::getProps()
{
    return this->myProps;
}

void HTMLNode::setTag(std::string theTag)
{
    this->myTag = theTag;
}

void HTMLNode::setValue(std::string theValue)
{
    this->myValue = theValue;
}

void HTMLNode::setProps(std::map<std::string, std::pair<std::string, std::string>> theProps)
{
    this->myProps = theProps;
}
