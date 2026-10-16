
#include "htmlnode.hpp"

HTMLNode::HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::pair<std::string, std::string>> theProps)
{
    myTag = theTag;
    myValue = theValue;
    myChildren = theChildren;
    myProps = theProps;
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

std::vector<HTMLNode> HTMLNode::textToChildren(std::string theText)
{
    std::vector<HTMLNode> children;

    TextNode node("hi", TextType::Text);

    std::vector<TextNode> nodeList = node.textToTextNode(theText);

    for (const TextNode& tNode : nodeList)
    {
        children.push_back(tNode.textNodeToHTMLNode());
    }

    return children;
}

HTMLNode HTMLNode::markdownToHTML(std::string theMarkdown)
{
    TextNode node("hi", TextType::Text);

    std::vector<std::string> blocks = node.markdownToBlocks(theMarkdown);

    for (std::string block : blocks)
    {
        BlockType type = node.blockToBlockType(block);
        std::string opening;
        std::string closing;

        switch (type)
        {
            case BlockType::Heading:
            {
                int num = 0;

                for (char ch : theMarkdown)
                {
                    if (ch != '#')
                        break;
                    else
                        num++;
                }

                opening = "<h" + std::to_string(num) + ">";
                closing = "</h" + std::to_string(num) + ">";


            }
            case BlockType::Code:
            {
                opening = "<pre><code>";
                closing = "</code></pre>";


            }
            case BlockType::Quote:
            {
                opening = "<blockquote>";
                closing = "</blockquote>";


            }
            case BlockType::UnorderedList:
            {
                opening = "<ul>\n   ";
                closing = "\n</ul>";


            }
            case BlockType::OrderedList:
            {
                opening = "<ol>\n   ";
                closing = "\n</ol>";

                
            }
            case BlockType::Paragraph:
            {
                opening = "<p>";
                closing = "</p>";


            }
        }
    }
}

std::string HTMLNode::getTag() const
{
    return myTag;
}

std::string HTMLNode::getValue() const
{
    return myValue;
}

const std::vector<HTMLNode>& HTMLNode::getChildren() const
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
