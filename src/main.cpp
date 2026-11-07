
#include <iostream>

#include "filemove.hpp"
#include "generator.hpp"

int main(int argc, char* argv[])
{
    std::string basepath = "/";

    if (argc > 1)
    {
        basepath = argv[1];
    }
    
    SiteGenerator sg;
    sg.generatePagesRecursive("content", "template.html", "docs", basepath);

    return 0;
}
