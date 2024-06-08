#include "swpch.hpp"
#include "EngineConfiguration.hpp"

namespace swheel {
    EngineConfiguration::EngineConfiguration(): m_arguments("") {
        m_arguments.AddArgument(cli::Argument("resources-path", "r", "PATH",
            "Resources directory path", &m_resourcesPath, cli::Argument::Type::STRING));
    }
    
    EngineConfiguration::~EngineConfiguration() {}

    bool EngineConfiguration::ParseArguments(int argc, char** argv) {
        return m_arguments.ParseArguments(argc, argv);
    }
}
