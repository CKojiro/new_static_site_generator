
#include "filemove.hpp"

void copyDirectory(const fs::path& source, const fs::path& destination)
{
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
        {
            std::cerr << "Source directory does not exist or is not a directory.";
            return;
        }

        if (!fs::exists(destination))
        {
            fs::create_directories(destination);
        }

        fs::copy_options options = fs::copy_options::recursive;

        fs::remove_all(destination);

        fs::copy(source, destination, options);
    }
    catch(const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    
}
