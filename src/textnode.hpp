
#include <string>
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
    bool equals(const TextNode& other);
    std::string stringRepresentation();
};
