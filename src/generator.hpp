
#pragma once

#include <regex>
#include <string>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

std::string extractTitle(const std::string& theMarkdown);

class SiteGenerator
{
private:
public:


    void generatePage(fs::path& fromPath, fs::path& templatePath, fs::path& destinationPath);
};
