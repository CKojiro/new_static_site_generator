
#include "htmlnode.hpp"

class LeafNode : public HTMLNode
{
private:


public:
    LeafNode(std::string theTag, std::string theValue,
        std::map<std::string, std::string> theProps);

    void toHTML();
};
