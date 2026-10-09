
#include <regex>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "leafnode.hpp"

enum class TextType
{
    Text,
    Bold,
    Italic,
    Code,
    Link,
    Image
};

class TextNode
{
private:
    std::string myText;
    TextType myTextType;
    std::string myUrl;

public:
    TextNode(std::string theText, TextType theTextType);
    TextNode(std::string theText, TextType theTextType, std::string theUrl);

    bool equals(const TextNode& other);
    std::string stringRepresentation();

    LeafNode textNodeToHTMLNode();
    std::vector<TextNode> splitNodesDelimiter(const std::vector<TextNode>& oldNodes,
        std::string delimiter, TextType textType);
    
    std::map<std::string, std::string> extractMarkdownImages(std::string theText);
    std::map<std::string, std::string> extractMarkdownLinks(std::string theText);

    std::vector<TextNode> splitNodesImage(const std::vector<TextNode>& oldNodes);
    std::vector<TextNode> splitNodesLink(const std::vector<TextNode>& oldNodes);

    std::vector<TextNode> textToTextNode(std::string theText);
};
