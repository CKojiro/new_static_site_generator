
#include "parentnode.hpp"

ParentNode::ParentNode(std::string theTag,
    std::vector<std::unique_ptr<HTMLNode>> theChildren)
    : HTMLNode(theTag, "", std::move(theChildren), {})
{}

ParentNode::ParentNode(std::string theTag,
    std::vector<std::unique_ptr<HTMLNode>> theChildren,
    std::map<std::string, std::pair<std::string, std::string>> theProps)
    : HTMLNode(theTag, "", std::move(theChildren), theProps)
{}

std::string ParentNode::toHTML()
{
    if (getTag() == "")
    {
        throw std::invalid_argument("ParentNode must have a tag.");
    }

    if (getChildren().empty())
    {
        throw std::invalid_argument("ParentNode must have children.");
    }
    
    std::stringstream output;

    output << "<" << getTag() << ">";

    for (const auto& node : getChildren())
    {
        if (node->getTag() == "")
        {
            output << node->getValue();
        }
        else
        {
            output << "<" << node->getTag() << ">" << node->getValue();
            output << "</" << node->getTag() << ">";
        }
    }

    output << "</" << getTag() << ">";

    return output.str();
}
