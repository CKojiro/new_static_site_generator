
#include "generator.hpp"

std::string extractTitle(const std::string& theMarkdown)
{
    std::string output;
    std::stringstream ss(theMarkdown);

    std::regex pattern(R"(^# [^#\s].*)");

    while (std::getline(ss, output))
    {
        if (!output.empty() && std::regex_search(output, pattern))
        {
            output.erase(0, 2);
        
            break;
        }
    }

    return output;
}

void SiteGenerator::generatePage(fs::path& fromPath,
    fs::path& templatePath, fs::path& destinationPath)
{
    std::cout << "Generating page from " << fromPath.string()
        << " to " << destinationPath.string() << " using " << templatePath.string();

    std::ifstream mFile(fromPath);
    std::stringstream mBuffer;
    mBuffer << mFile.rdbuf();
    std::string markdown = mBuffer.str();

    std::ifstream tFile(templatePath);
    std::stringstream tBuffer;
    tBuffer << tFile.rdbuf();
    std::string templateFile = tBuffer.str();

    markdownToHTML();

    extractTitle();

    
}
