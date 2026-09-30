
#include "htmlnode.hpp"

class LeafNode : HTMLNode
{
private:


public:
    LeafNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::string> theProps);

    void toHTML();
};
