
#include "converter.hpp"

std::unique_ptr<HTMLNode> markdownToHTML(std::string theMarkdown)
{
    TextNode node("hi", TextType::Text);

    std::vector<std::string> blocks = node.markdownToBlocks(theMarkdown);

    std::vector<std::unique_ptr<HTMLNode>> children;

    for (int i = 0; i < blocks.size(); i++)
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
                tag = "code";
                value = ;

                children.push_back(std::make_unique<ParentNode>("pre", ));

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
                opening = "<ul>\n   ";
                closing = "\n</ul>";

                children.push_back(std::make_unique<ParentNode>("ul", ));

                break;
            }
            case BlockType::OrderedList:
            {
                opening = "<ol>\n   ";
                closing = "\n</ol>";

                children.push_back(std::make_unique<ParentNode>("ol", ));

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

    //HTMLNode output("div", "", std::move(children), {});

    return std::make_unique<ParentNode>("div", std::move(children));
}
