
#include "textnode.hpp"

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
    std::string output;

    switch (myTextType)
    {
        case TextType::Text:
            break;
        case TextType::Bold:
            break;
        case TextType::Italic:
            break;
        case TextType::Code:
            break;
        case TextType::Link:
            break;
        case TextType::Image:
            break;
        default:
            break;
    }

    return output;
}
