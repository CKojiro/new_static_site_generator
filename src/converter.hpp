
#pragma once

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

std::vector<std::unique_ptr<HTMLNode>> textToChildren(std::string theText);

LeafNode textNodeToHTMLNode(TextNode theNode);
