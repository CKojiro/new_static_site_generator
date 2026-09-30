
#include "leafnode.hpp"

LeafNode::LeafNode(std::string theTag, std::string theValue)
    : HTMLNode(theTag, theValue, {}, {}) {}

LeafNode::LeafNode(std::string theTag, std::string theValue,
    std::map<std::string, std::string> theProps)
    : HTMLNode(theTag, theValue, {}, theProps) {}

std::string LeafNode::toHTML()
{
    if (getValue() == "")
    {
        throw std::invalid_argument("LeafNode must have a value.");
    }

    std::stringstream output;

    if (getTag() == "")
    {
        return getValue();
    }
    else if (getProps().empty())
    {
        output << "<" << getTag() << ">";
        output << getValue() << "</" << getTag() << ">";
    }
    else
    {
        auto [key, value] = *getProps().begin();
        output << "<" << getTag();
        output << " " << key << "=" << "\"" << value << "\">";
        output << getValue() << "</" << getTag() << ">";
    }

    return output.str();
}

std::string LeafNode::stringRepresentation()
{
    std::stringstream output;

    output << "tag = " << getTag() << "\n" << "value = " << getValue()
        << "\n" << "props = {";

    for (const auto& [key, value] : getProps())
    {
        output << "{" << key << ", " << value << "}, ";
    }

    output << "}";

    return output.str();
}
