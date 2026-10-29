
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

std::vector<std::unique_ptr<HTMLNode>> textToChildren(std::string theText)
{
    std::vector<std::unique_ptr<HTMLNode>> children;

    std::vector<TextNode> nodeList = node.textToTextNode(theText);

    for (const TextNode& tNode : nodeList)
    {
        children.push_back(std::make_unique<LeafNode>(textNodeToHTMLNode()));
    }

    return children;
}

LeafNode textNodeToHTMLNode(TextNode theNode)
{
    switch (theNode.getTextType())
    {
        case TextType::Text:
            return LeafNode("", theNode.getText());
            break;
        case TextType::Bold:
            return LeafNode("b", theNode.getText());
            break;
        case TextType::Italic:
            return LeafNode("i", theNode.getText());
            break;
        case TextType::Code:
            return LeafNode("code", theNode.getText());
            break;
        case TextType::Link:
            return LeafNode("a", theNode.getText(), {{"a", {"href", theNode.getUrl()}}});
            break;
        case TextType::Image:
            return LeafNode("img", "", {{"img", {"src", ""}}, {"img", {"alt", ""}}});
            break;
        default:
            throw std::invalid_argument("TextType is not one of the allowed types.");
            break;
    }
}
