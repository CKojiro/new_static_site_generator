
#include "parentnode.hpp"

ParentNode::ParentNode(std::string theTag,
    std::vector<HTMLNode> theChildren)
    : HTMLNode(theTag, "", theChildren, {}) {}

ParentNode::ParentNode(std::string theTag,
    std::vector<HTMLNode> theChildren,
    std::map<std::string, std::pair<std::string, std::string>> theProps)
    : HTMLNode(theTag, "", theChildren, theProps) {}

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

    

    return output.str();
}
