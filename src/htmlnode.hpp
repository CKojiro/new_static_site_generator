
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>

#include "textnode.hpp"

class HTMLNode
{
private:
    std::string myTag;
    std::string myValue;
    std::vector<HTMLNode> myChildren;
    std::map<std::string, std::pair<std::string, std::string>> myProps;

public:
    HTMLNode(std::string theTag, std::string theValue,
        std::vector<HTMLNode> theChildren,
        std::map<std::string, std::pair<std::string, std::string>> theProps);

    virtual std::string toHTML();
    std::string propsToHTML();
    virtual std::string stringRepresentation();

    HTMLNode markdownToHTML(std::string theMarkdown);

    std::string getTag() const;
    std::string getValue() const;
    const std::vector<HTMLNode>& getChildren() const;
    const std::map<std::string, std::pair<std::string, std::string>>& getProps() const;

    void setTag(std::string theTag);
    void setValue(std::string theValue);
    void setProps(std::map<std::string, std::pair<std::string, std::string>> theProps);
};
