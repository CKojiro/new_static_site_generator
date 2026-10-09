
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

std::map<std::string, std::string> TextNode::extractMarkdownImages(std::string theText)
{
    std::map<std::string, std::string> output;

    std::regex patternOne(R"(!\[([^\]]+)\]\(([^)]+)\))");

    auto markdownBegin = std::sregex_iterator(theText.begin(), theText.end(), patternOne);
    auto markdownEnd = std::sregex_iterator();

    for (std::sregex_iterator i = markdownBegin; i != markdownEnd; i++)
    {
        std::smatch match = *i;
        
        std::string textOne = match[1].str();
        std::string textTwo = match[2].str();

        output.emplace(textOne, textTwo);
    }

    return output;
}

std::map<std::string, std::string> TextNode::extractMarkdownLinks(std::string theText)
{
    std::map<std::string, std::string> output;

    std::regex patternOne(R"(\[([^\]]+)\]\(([^)]+)\))");

    auto markdownBegin = std::sregex_iterator(theText.begin(), theText.end(), patternOne);
    auto markdownEnd = std::sregex_iterator();

    for (std::sregex_iterator i = markdownBegin; i != markdownEnd; i++)
    {
        std::smatch match = *i;
        
        std::string textOne = match[1].str();
        std::string textTwo = match[2].str();

        output.emplace(textOne, textTwo);
    }

    return output;
}

std::vector<TextNode> TextNode::splitNodesImage(const std::vector<TextNode>& oldNodes)
{
    std::vector<TextNode> output;

    std::regex pattern(R"(!\[([^\]]+)\]\(([^)]+)\))");

    for (const auto& node : oldNodes)
    {
        size_t position = 0;

        auto matchesBegin = std::sregex_iterator(node.myText.begin(),
            node.myText.end(), pattern);
        auto matchesEnd = std::sregex_iterator();

        for (std::sregex_iterator i = matchesBegin; i != matchesEnd; i++)
        {
            std::smatch match = *i;

            auto index = match.position();

            std::string textOne = node.myText.substr(position, index - position);
            std::string textTwo = match[1].str();
            std::string textThree = match[2].str();

            output.push_back(TextNode(textOne, TextType::Text));
            output.push_back(TextNode(textTwo, TextType::Link, textThree));

            position = match.position() + match.length();
        }

        std::string finalText = node.myText.substr(position);

        if (!finalText.empty())
        {
            output.push_back(TextNode(finalText, TextType::Text));
        }
    }

    return output;
}

std::vector<TextNode> TextNode::splitNodesLink(const std::vector<TextNode>& oldNodes)
{
    std::vector<TextNode> output;

    std::regex pattern(R"(\[([^\]]+)\]\(([^)]+)\))");

    for (const auto& node : oldNodes)
    {
        size_t position = 0;

        auto matchesBegin = std::sregex_iterator(node.myText.begin(),
            node.myText.end(), pattern);
        auto matchesEnd = std::sregex_iterator();

        for (std::sregex_iterator i = matchesBegin; i != matchesEnd; i++)
        {
            std::smatch match = *i;

            auto index = match.position();

            std::string textOne = node.myText.substr(position, index - position);
            std::string textTwo = match[1].str();
            std::string textThree = match[2].str();

            output.push_back(TextNode(textOne, TextType::Text));
            output.push_back(TextNode(textTwo, TextType::Link, textThree));

            position = match.position() + match.length();
        }

        std::string finalText = node.myText.substr(position);

        if (!finalText.empty())
        {
            output.push_back(TextNode(finalText, TextType::Text));
        }
    }

    return output;
}

std::vector<TextNode> TextNode::textToTextNode(std::string theText)
{
    std::vector<TextNode> output;
    std::vector<TextNode> firstRun;
    std::vector<TextNode> secondRun;
    char previous = '\0';
    int position = 0;
    int i = 0;
    std::string text = "";

    for (i = 0; i < theText.length(); i++)
    {
        switch (theText[i])
        {
            case '*':
            {
                text = theText.substr(position, i - position);
                
                if (!text.empty())
                    firstRun.push_back(TextNode(text, TextType::Text));

                position = i;
                i = theText.find('*', position + 2);
                text = theText.substr(position + 2, i - position);
                firstRun.push_back(TextNode(text, TextType::Bold));
                i += 2;
                continue;
            }
            case '_':
            {
                text = theText.substr(position, i - position);

                if (!text.empty())
                    firstRun.push_back(TextNode(text, TextType::Text));

                position = i;
                i = theText.find('_', position + 1);
                text = theText.substr(position + 1, i - position);
                firstRun.push_back(TextNode(text, TextType::Italic));
                i++;
                continue;
            }
            case '`':
            {
                text = theText.substr(position, i - position);
                
                if (!text.empty())
                    firstRun.push_back(TextNode(text, TextType::Text));
                
                position = i;
                i = theText.find('`', position + 1);
                text = theText.substr(position + 1, i - position);
                firstRun.push_back(TextNode(text, TextType::Code));
                i++;
                continue;
            }
            default:
                continue;
        }
            
        previous = theText[i];
    }

    std::vector<TextNode> newNodes = splitNodesImage(firstRun);

    for (TextNode node : newNodes)
    {
        secondRun.push_back(node);
    }

    std::vector<TextNode> newNodes = splitNodesLink(secondRun);

    for (TextNode node : newNodes)
    {
        output.push_back(node);
    }

    text = theText.substr(i);
    output.push_back(TextNode(text, TextType::Text));

    return output;
}
