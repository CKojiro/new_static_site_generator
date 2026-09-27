
#include <string>
#include <sstream>
#include <iostream>

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
    TextNode(std::string theText, TextType theTextType, std::string theUrl);

    bool equals(const TextNode& other);
    std::string stringRepresentation();
};
