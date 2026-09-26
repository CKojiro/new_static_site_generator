
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
