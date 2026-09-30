
#include "leafnode.hpp"

LeafNode::LeafNode(std::string theTag, std::string theValue,
    std::map<std::string, std::string> theProps)
{
    setTag(theTag);
    setValue(theValue);
    setProps(theProps);
}

void LeafNode::toHTML()
{
    
}
