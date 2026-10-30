
#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <cctype>
#include <sstream>
#include <algorithm>
#include "textnode.hpp"
#include "htmlnode.hpp"
#include "parentnode.hpp"
#include "leafnode.hpp"

std::unique_ptr<HTMLNode> markdownToHTML(std::string theMarkdown);

std::vector<TextNode> splitNodesImage(const std::vector<TextNode>& oldNodes);
std::vector<TextNode> splitNodesLink(const std::vector<TextNode>& oldNodes);

std::vector<TextNode> textToTextNode(std::string theText);

std::vector<std::unique_ptr<HTMLNode>> textToChildren(const std::string& theText);

std::unique_ptr<HTMLNode> textNodeToHTMLNode(const TextNode& theNode);
