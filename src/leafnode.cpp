
#include "leafnode.hpp"

LeafNode::LeafNode(std::string theTag, std::string theValue)
    : HTMLNode(theTag, theValue, {}, {}) {}

LeafNode::LeafNode(std::string theTag, std::string theValue,
    std::map<std::string, std::pair<std::string, std::string>> theProps)
    : HTMLNode(theTag, theValue, {}, theProps) {}

LeafNode::LeafNode(LeafNode&& theNode) noexcept
    : HTMLNode(std::move(theNode)) {}

std::string LeafNode::toHTML()
{
    std::stringstream output;

    if (getTag() == "")
    {
        return getValue();
    }

    output << "<" << getTag();

    for (const auto& [mapKey, innerPair] : getProps())
    {
        const auto& [key, value] = innerPair;

        output << " " << key << "=" << "\"" << value << "\"";
    }

    if (getTag() == "img")
    {
        output << " />";
    }
    else
    {
        output << ">" << getValue() << "</" << getTag() << ">";
    }

    return output.str();
}

std::string LeafNode::stringRepresentation()
{
    std::stringstream output;

    output << "tag = " << getTag() << "\n" << "value = " << getValue()
        << "\n" << "props = {";

    for (const auto& [tag, nestedPair] : getProps())
    {
        const auto& [key, value] = nestedPair;
        output << "{" << key << ", " << value << "},\n";
    }

    output << "}";

    return output.str();
}
