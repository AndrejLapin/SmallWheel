#include "swpch.hpp"
#include "EngineConfiguration.hpp"

namespace swheel {
    EngineConfiguration::EngineConfiguration() {
        m_arguments = cli::Arguments("");
        m_arguments.AddArgument(cli::Argument("resources-path", "r", "PATH",
            "Resources directory path", &m_resourcesPath, cli::Argument::Type::STRING));
    }
    
    EngineConfiguration::~EngineConfiguration() {}

    void EngineConfiguration::ParseArguments(int argc, char** argv) {
        m_arguments.ParseArguments(argc, argv);
    }
}
