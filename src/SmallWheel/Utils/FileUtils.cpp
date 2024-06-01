#include "swpch.hpp"
#include "FileUtils.hpp"

#include "SmallWheel/Core.hpp"

namespace swheel::fileUtils {
    std::string GetFileContents(const std::filesystem::path& path) {
        std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
        SW_ASSERT_LOG(file.is_open(), "Unable to open file at path: " + path.string());
        size_t size = file.tellg();
        std::string buffer(size, '\0');
        file.seekg(0);
        file.read(buffer.data(), size);
        file.close();
        return buffer;
    }
}
