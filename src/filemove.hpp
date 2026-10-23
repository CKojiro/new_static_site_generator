
#pragma once

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void copyDirectory(const fs::path& source, const fs::path& destination);

void deleteDirectoryContents(const fs::path& directory);
