
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <map>

#include "textnode.hpp"

class HTMLNode
{
private:
    std::string myTag;
    std::string myValue;
    std::vector<std::unique_ptr<HTMLNode>> myChildren;
    std::map<std::string, std::pair<std::string, std::string>> myProps;

public:
    HTMLNode(std::string theTag, std::string theValue,
        std::vector<std::unique_ptr<HTMLNode>> theChildren,
        std::map<std::string, std::pair<std::string, std::string>> theProps);

    virtual ~HTMLNode() = default;

    virtual std::string toHTML();
    std::string propsToHTML();
    virtual std::string stringRepresentation();

    std::vector<HTMLNode> textToChildren(std::string theText);

    HTMLNode markdownToHTML(std::string theMarkdown);

    std::string getTag() const;
    std::string getValue() const;
    const std::vector<std::unique_ptr<HTMLNode>>& getChildren() const;
    const std::map<std::string, std::pair<std::string, std::string>>& getProps() const;

    void setTag(std::string theTag);
    void setValue(std::string theValue);
    void setProps(std::map<std::string, std::pair<std::string, std::string>> theProps);
};
