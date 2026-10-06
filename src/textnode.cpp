
#include "textnode.hpp"

TextNode::TextNode(std::string theText, TextType theTextType)
{
    myText = theText;
    myTextType = theTextType;
}

TextNode::TextNode(std::string theText, TextType theTextType, std::string theUrl)
{
    myText = theText;
    myTextType = theTextType;
    myUrl = theUrl;
}

bool TextNode::equals(const TextNode& other)
{
    const TextNode* tPointer = dynamic_cast<const TextNode*>(&other);

    if (!tPointer) return false;

    bool output = (this->myText == tPointer->myText) &&
        (this->myTextType == tPointer->myTextType) &&
        (this->myUrl == tPointer->myUrl);

    return output;
}

std::string TextNode::stringRepresentation()
{
    std::stringstream output;

    switch (myTextType)
    {
        case TextType::Text:
            output << "TextNode(" << myText << ", " << "text" << ", " << myUrl << ")";
            break;
        case TextType::Bold:
            output << "TextNode(" << myText << ", " << "bold" << ", " << myUrl << ")";
            break;
        case TextType::Italic:
            output << "TextNode(" << myText << ", " << "italic" << ", " << myUrl << ")";
            break;
        case TextType::Code:
            output << "TextNode(" << myText << ", " << "code" << ", " << myUrl << ")";
            break;
        case TextType::Link:
            output << "TextNode(" << myText << ", " << "link" << ", " << myUrl << ")";
            break;
        case TextType::Image:
            output << "TextNode(" << myText << ", " << "image" << ", " << myUrl << ")";
            break;
        default:
            break;
    }

    return output.str();
}

LeafNode TextNode::textNodeToHTMLNode()
{
    switch (myTextType)
    {
        case TextType::Text:
            return LeafNode("", myText);
            break;
        case TextType::Bold:
            return LeafNode("b", myText);
            break;
        case TextType::Italic:
            return LeafNode("i", myText);
            break;
        case TextType::Code:
            return LeafNode("code", myText);
            break;
        case TextType::Link:
            return LeafNode("a", myText, {{"a", {"href", myText}}});
            break;
        case TextType::Image:
            return LeafNode("img", "", {{"img", {"src", ""}}, {"img", {"alt", ""}}});
            break;
        default:
            throw std::invalid_argument("TextType is not one of the allowed types.");
            break;
    }
}

std::vector<TextNode> TextNode::splitNodesDelimiter(
    const std::vector<TextNode>& oldNodes,
    std::string delimiter, TextType textType)
{
    std::vector<TextNode> newNodes;

    for (const TextNode& node : oldNodes)
    {
        size_t position = 0;
        TextType currentType = TextType::Text;

        while (position < node.myText.length())
        {
            auto index = node.myText.find(delimiter, position);

            if (index == std::string::npos)
            {
                if (currentType == textType)
                {
                    throw std::invalid_argument("Missing second delimiter.");
                }
                else
                {
                    newNodes.push_back(TextNode(node.myText.substr(position), TextType::Text));
                    break;
                }
            }
            else
            {
                std::string text = node.myText.substr(position, index - position);

                newNodes.push_back(TextNode(text, currentType));

                position = index + delimiter.length();

                if (currentType == TextType::Text)
                    currentType = textType;
                else
                    currentType = TextType::Text;
            }
        }
    }

    return newNodes;
}
