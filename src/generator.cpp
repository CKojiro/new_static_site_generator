
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
