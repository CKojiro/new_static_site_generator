
#pragma once

#include "htmlnode.hpp"

class ParentNode : public HTMLNode
{
private:

public:
    ParentNode(std::string theTag,
        std::vector<HTMLNode> theChildren);

    ParentNode(std::string theTag,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::pair<std::string, std::string>> theProps);

    std::string toHTML() override;
};
