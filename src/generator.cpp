
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

    std::string htmlContents = markdownToHTML(markdown).toHTML();

    std::string titleString = extractTitle(markdown);

    std::size_t titlePos = templateFile.find("{{ Title }}");

    if (titlePos != std::string::npos)
    {
        templateFile.replace(titlePos, std::string("{{ Title }}").length(), titleString);
    }

    std::size_t contentsPos = templateFile.find("{{ Contents }}");

    if (contentsPos != std::string::npos)
    {
        templateFile.replace(contentsPos, std::string("{{ Contents }}").length(), htmlContents);
    }

    if (destinationPath.has_parent_path())
        fs::create_directories(destinationPath.parent_path());

    std::ofstream outFile(destinationPath);

    if (!outFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    outFile << templateFile << std::endl;

    outFile.close();
}
