
#include "filemove.hpp"

void copyDirectory(const fs::path& source, const fs::path& destination)
{
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
        {
            std::cerr << "Source directory does not exist or is not a directory." << std::endl;
            return;
        }

        if (!fs::exists(destination))
        {
            fs::create_directories(destination);
        }
        else if (fs::is_directory(destination))
        {
            deleteDirectoryContents(destination);
        }
        else
        {
            std::cerr << "Destination is not a directory." << std::endl;
            return;
        }

        fs::copy_options options = fs::copy_options::recursive;

        fs::copy(source, destination, options);
    }
    catch(const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    
}

bool deleteDirectoryContents(const fs::path& directory)
{
    if (!fs::exists(directory) || !fs::is_directory(directory))
    {
        std::cerr << "Path does not exist or is not a directory." << std::endl;
        return false;
    }

    for (const auto& entry : fs::directory_iterator(directory))
    {
        std::error_code ec;

        fs::remove_all(entry.path(), ec);

        if (ec)
        {
            std::cerr << "Failed to delete: "
                << entry.path() << " | "
                << ec.message() << std::endl;
        }
    }

    return true;
}
