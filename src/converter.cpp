
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
                std::stringstream os;
                std::string line;
                std::vector<std::string> lines;

                while(std::getline(ss, line, '\n'))
                {
                    lines.push_back(line);
                }

                for (const auto& l : lines)
                {
                    if (!l.empty())
                        l.erase(0, 2);
                    
                    os << l << "\n";
                }

                tag = "li";
                
                value = os.str();

                std::vector<std::unique_ptr<HTMLNode>> items;

                items.push_back(std::make_unique<LeafNode>(tag, value));

                children.push_back(
                    std::make_unique<ParentNode>("ul", std::move(items)));

                break;
            }
            case BlockType::OrderedList:
            {
                std::string content = blocks[i];

                std::stringstream ss(content);
                std::stringstream os;
                std::string line;
                std::vector<std::string> lines;

                while(std::getline(ss, line, '\n'))
                {
                    lines.push_back(line);
                }

                for (const auto& l : lines)
                {
                    if (!l.empty())
                        l.erase(0, 2);
                    
                    os << l << "\n";
                }

                tag = "li";
                
                value = os.str();

                std::vector<std::unique_ptr<HTMLNode>> items;

                items.push_back(std::make_unique<LeafNode>(tag, value));

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
