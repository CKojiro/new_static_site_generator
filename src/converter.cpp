
#include "converter.hpp"

std::unique_ptr<HTMLNode> markdownToHTML(std::string theMarkdown)
{
    TextNode node("hi", TextType::Text);

    std::vector<std::string> blocks = node.markdownToBlocks(theMarkdown);

    std::vector<std::unique_ptr<HTMLNode>> children;

    for (size_t i = 0; i < blocks.size(); i++)
    {
        BlockType type = node.blockToBlockType(blocks[i]);
        std::string tag;
        std::string value;

        switch (type)
        {
            case BlockType::Heading:
            {
                int num = 0;
                std::string content = blocks[i];

                for (char ch : content)
                {
                    if (num > 5)
                        break;
                    
                    if (ch != '#')
                        break;
                    else
                        num++;
                }

                tag = "h" + std::to_string(num);

                size_t pos = content.find_first_not_of('#');

                if (pos != std::string::npos)
                    content.erase(0, pos);
                else
                    content.clear();

                if (!content.empty() && std::isspace(static_cast<unsigned char>(content[0])))
                    content.erase(0, 1);

                value = content;

                children.push_back(std::make_unique<LeafNode>(tag, value));

                break;
            }
            case BlockType::Code:
            {
                std::string content = blocks[i];

                tag = "code";

                if (!content.empty())
                    content.erase(0, 4);

                if (content.length() >= 3)
                    content.erase(content.length() - 3);
                
                value = content;

                std::vector<std::unique_ptr<HTMLNode>> items;

                items.push_back(std::make_unique<LeafNode>(tag, value));

                children.push_back(
                    std::make_unique<ParentNode>("pre", std::move(items)));

                break;
            }
            case BlockType::Quote:
            {
                std::string content = blocks[i];

                tag = "blockquote";

                if (!content.empty())
                    content.erase(0, 2);

                value = content;

                children.push_back(std::make_unique<LeafNode>(tag, value));

                break;
            }
            case BlockType::UnorderedList:
            {
                std::string content = blocks[i];
                std::stringstream ss(content);
                std::string line;
                std::vector<std::unique_ptr<HTMLNode>> items;

                tag = "li";

                while (std::getline(ss, line, '\n'))
                {
                    if (!line.empty())
                        line.erase(0, 2);

                    items.push_back(std::make_unique<LeafNode>(tag, line));
                }

                children.push_back(
                    std::make_unique<ParentNode>("ul", std::move(items)));

                break;
            }
            case BlockType::OrderedList:
            {
                std::string content = blocks[i];
                std::stringstream ss(content);
                std::string line;
                char period = '.';
                std::vector<std::unique_ptr<HTMLNode>> items;

                tag = "li";

                while (std::getline(ss, line, '\n'))
                {
                    size_t index = 0;

                    if (line.find(period) != std::string::npos)
                    {
                        index = line.find(period);
                        std::string num = line.substr(0, index);

                        if (num.empty() ||
                            !(std::all_of(num.begin(), num.end(),
                            [](unsigned char c) { return std::isdigit(c); })))
                        {
                            index = 0;
                        }
                    }
                    

                    if (!line.empty() && index > 0)
                        line.erase(0, index + 1);
                    
                    size_t first = line.find_first_not_of(' ');

                    if (first != std::string::npos)
                        line.erase(0, first);
                    else
                        line.clear();

                    items.push_back(std::make_unique<LeafNode>(tag, line));
                }

                children.push_back(
                    std::make_unique<ParentNode>("ol", std::move(items)));

                break;
            }
            case BlockType::Paragraph:
            {
                std::string content = blocks[i];
                
                tag = "p";
                value = content;
                
                children.push_back(std::make_unique<LeafNode>(tag, value));

                break;
            }
        }
    }

    return std::make_unique<ParentNode>("div", std::move(children));
}

std::vector<TextNode> splitNodesImage(const std::vector<TextNode>& oldNodes)
{
    std::vector<TextNode> output;

    std::regex pattern(R"(!\[([^\]]+)\]\(([^)]+)\))");

    for (const auto& node : oldNodes)
    {
        size_t position = 0;

        auto matchesBegin = std::sregex_iterator(node.getText().begin(),
            node.getText().end(), pattern);
        auto matchesEnd = std::sregex_iterator();

        for (std::sregex_iterator i = matchesBegin; i != matchesEnd; i++)
        {
            std::smatch match = *i;

            auto index = match.position();

            std::string textOne = node.getText().substr(position, index - position);
            std::string textTwo = match[1].str();
            std::string textThree = match[2].str();

            if (!textOne.empty())
                output.push_back(TextNode(textOne, TextType::Text));
            
            output.push_back(TextNode(textTwo, TextType::Image, textThree));

            position = match.position() + match.length();
        }

        std::string finalText = node.getText().substr(position);

        if (!finalText.empty())
        {
            output.push_back(TextNode(finalText, TextType::Text));
        }
    }

    return output;
}

std::vector<TextNode> splitNodesLink(const std::vector<TextNode>& oldNodes)
{
    std::vector<TextNode> output;

    std::regex pattern(R"(\[([^\]]+)\]\(([^)]+)\))");

    for (const auto& node : oldNodes)
    {
        size_t position = 0;

        auto matchesBegin = std::sregex_iterator(node.getText().begin(),
            node.getText().end(), pattern);
        auto matchesEnd = std::sregex_iterator();

        for (std::sregex_iterator i = matchesBegin; i != matchesEnd; i++)
        {
            std::smatch match = *i;

            auto index = match.position();

            std::string textOne = node.getText().substr(position, index - position);
            std::string textTwo = match[1].str();
            std::string textThree = match[2].str();

            if (!textOne.empty())
                output.push_back(TextNode(textOne, TextType::Text));

            output.push_back(TextNode(textTwo, TextType::Link, textThree));

            position = match.position() + match.length();
        }

        std::string finalText = node.getText().substr(position);

        if (!finalText.empty())
        {
            output.push_back(TextNode(finalText, TextType::Text));
        }
    }

    return output;
}

std::vector<TextNode> textToTextNode(std::string theText)
{
    std::vector<TextNode> output;
    std::vector<TextNode> firstRun;
    std::vector<TextNode> secondRun;
    std::string::size_type position = 0;
    std::string::size_type i = 0;
    std::string text = "";

    while (i < theText.length())
    {
        switch (theText[i])
        {
            case '*':
            {
                if (i + 1 < theText.length() && theText[i + 1] == '*')
                {
                    text = theText.substr(position, i - position);
                
                    if (!text.empty())
                        firstRun.push_back(TextNode(text, TextType::Text));

                    position = i;
                    auto closing = theText.find("**", position + 2);

                    if (closing == std::string::npos)
                    {
                        throw std::invalid_argument("Closing delimiter not found.");
                    }

                    i = closing;
                    text = theText.substr(position + 2, i - (position + 2));
                    firstRun.push_back(TextNode(text, TextType::Bold));
                    i += 2;
                    position = i;
                    continue;
                }
                else
                {
                    i++;
                    continue;
                }
                
            }
            case '_':
            {
                text = theText.substr(position, i - position);

                if (!text.empty())
                    firstRun.push_back(TextNode(text, TextType::Text));

                position = i;
                auto closing = theText.find('_', position + 1);

                if (closing == std::string::npos)
                {
                    throw std::invalid_argument("Closing delimiter not found.");
                }

                i = closing;
                text = theText.substr(position + 1, i - (position + 1));
                firstRun.push_back(TextNode(text, TextType::Italic));
                i++;
                position = i;
                continue;
            }
            case '`':
            {
                text = theText.substr(position, i - position);
                
                if (!text.empty())
                    firstRun.push_back(TextNode(text, TextType::Text));
                
                position = i;
                auto closing = theText.find('`', position + 1);

                if (closing == std::string::npos)
                {
                    throw std::invalid_argument("Closing delimiter not found.");
                }
                
                i = closing;
                text = theText.substr(position + 1, i - (position + 1));
                firstRun.push_back(TextNode(text, TextType::Code));
                i++;
                position = i;
                continue;
            }
            default:
                i++;
                continue;
        }
    }

    std::string extraText = theText.substr(position);

    if (!extraText.empty())
        firstRun.push_back(TextNode(extraText, TextType::Text));

    std::vector<TextNode> newNodes = splitNodesImage(firstRun);

    for (TextNode node : newNodes)
    {
        secondRun.push_back(node);
    }

    newNodes = splitNodesLink(secondRun);

    for (TextNode node : newNodes)
    {
        output.push_back(node);
    }

    return output;
}

std::vector<std::unique_ptr<HTMLNode>> textToChildren(const std::string& theText)
{
    std::vector<TextNode> nodeList = textToTextNode(theText);

    std::vector<std::unique_ptr<HTMLNode>> children;
    children.reserve(nodeList.size());

    for (const TextNode& tNode : nodeList)
    {
        children.push_back(textNodeToHTMLNode(tNode));
    }

    return children;
}

std::unique_ptr<HTMLNode> textNodeToHTMLNode(const TextNode& theNode)
{
    switch (theNode.getTextType())
    {
        case TextType::Text:
            return std::make_unique<LeafNode>("", theNode.getText());
        case TextType::Bold:
            return std::make_unique<LeafNode>("b", theNode.getText());
        case TextType::Italic:
            return std::make_unique<LeafNode>("i", theNode.getText());
        case TextType::Code:
            return std::make_unique<LeafNode>("code", theNode.getText());
        case TextType::Link:
            return std::make_unique<LeafNode>("a", theNode.getText(),
                std::map<std::string, std::pair<std::string, std::string>>{
                    {"a", {"href", theNode.getUrl()}}});
        case TextType::Image:
            return std::make_unique<LeafNode>("img", "",
                std::map<std::string, std::pair<std::string, std::string>>{
                    {"src", {"src", theNode.getUrl()}},
                    {"alt", {"alt", theNode.getText()}}});
        default:
            throw std::invalid_argument("TextType is not one of the allowed types.");
    }
}
