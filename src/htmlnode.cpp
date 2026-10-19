
#include "htmlnode.hpp"

HTMLNode::HTMLNode(std::string theTag,
    std::string theValue,
    std::vector<std::unique_ptr<HTMLNode>> theChildren,
    std::map<std::string, std::pair<std::string, std::string>> theProps)
    : myTag(std::move(theTag)),
      myValue(std::move(theValue)),
      myChildren(std::move(theChildren)),
      myProps(std::move(theProps))
{
}

HTMLNode::HTMLNode(HTMLNode&& theNode) noexcept
    : HTMLNode(std::move(theNode.myTag),
        std::move(theNode.myValue),
        std::move(theNode.myChildren),
        std::move(theNode.myProps))
{
}

std::string HTMLNode::toHTML()
{
    throw std::logic_error("Functionality not implemented!");

    return "";
}

std::string HTMLNode::propsToHTML()
{
    std::stringstream output;

    for (const auto& [tag, nestedPair]: myProps)
    {
        const auto& [key, value] = nestedPair;
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

std::vector<std::unique_ptr<HTMLNode>> HTMLNode::textToChildren(std::string theText)
{
    std::vector<std::unique_ptr<HTMLNode>> children;

    TextNode node("hi", TextType::Text);

    std::vector<TextNode> nodeList = node.textToTextNode(theText);

    for (const TextNode& tNode : nodeList)
    {
        children.push_back(std::make_unique<LeafNode>(tNode.textNodeToHTMLNode()));
    }

    return children;
}

std::string HTMLNode::getTag() const
{
    return myTag;
}

std::string HTMLNode::getValue() const
{
    return myValue;
}

const std::vector<std::unique_ptr<HTMLNode>>& HTMLNode::getChildren() const
{
    return myChildren;
}

const std::map<std::string, std::pair<std::string, std::string>>& HTMLNode::getProps() const
{
    return myProps;
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
