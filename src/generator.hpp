
#pragma once

#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "converter.hpp"

namespace fs = std::filesystem;

std::string extractTitle(const std::string& theMarkdown);

class SiteGenerator
{
private:
public:


    void generatePage(const fs::path& fromPath,
        const fs::path& templatePath, const fs::path& destinationPath);
};
