
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

HTMLNode HTMLNode::markdownToHTML(std::string theMarkdown)
{
    TextNode node("hi", TextType::Text);

    std::vector<std::string> blocks = node.markdownToBlocks(theMarkdown);

    ParentNode output("div", );

    for (int i = 1; i < blocks.size(); i++)
    {
        BlockType type = node.blockToBlockType(blocks[i]);
        std::string tag;
        std::string value;

        switch (type)
        {
            case BlockType::Heading:
            {
                int num = 0;

                for (char ch : blocks[i])
                {
                    if (num > 6)
                        break;
                    
                    if (ch != '#')
                        break;
                    else
                        num++;
                }

                tag = "h" + std::to_string(num);

                size_t pos = blocks[i].find_first_not_of('#');

                if (pos != std::string::npos)
                    blocks[i].erase(0, pos);
                else
                    blocks[i].clear();

                value = blocks[i];

                LeafNode(tag, value);

                break;
            }
            case BlockType::Code:
            {
                opening = "<pre><code>";
                closing = "</code></pre>";



                break;
            }
            case BlockType::Quote:
            {
                opening = "<blockquote>";
                closing = "</blockquote>";



                break;
            }
            case BlockType::UnorderedList:
            {
                opening = "<ul>\n   ";
                closing = "\n</ul>";



                break;
            }
            case BlockType::OrderedList:
            {
                opening = "<ol>\n   ";
                closing = "\n</ol>";



                break;
            }
            case BlockType::Paragraph:
            {
                opening = "<p>";
                closing = "</p>";

                

                break;
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
