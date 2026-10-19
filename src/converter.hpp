
#pragma once

#include <string>
#include <memory>
#include "htmlnode.hpp"
#include "parentnode.hpp"
#include "leafnode.hpp"

std::unique_ptr<HTMLNode> markdownToHTML(std::string theMarkdown);
