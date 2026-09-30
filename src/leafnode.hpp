
#pragma once

#include "htmlnode.hpp"

class LeafNode : public HTMLNode
{
private:


public:
    LeafNode(std::string theTag, std::string theValue);

    LeafNode(std::string theTag, std::string theValue,
        std::map<std::string, std::pair<std::string, std::string>> theProps);

    std::string toHTML() override;
    std::string stringRepresentation() override;
};
