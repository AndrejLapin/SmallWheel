#pragma once

#include "Utils/CLIArguments.hpp"

namespace swheel {

    /* TODO:
    * EngineConfiguration should be made to work like so:
    *   1. CreateApplication -> EngineConfiguration& gets passed to it or maybe better - have a pre parse method?
    *   2. User expands EngineConfiguration& with their desired arguments and also has the ability to remove arguments
    *   3. EngineConfiguration method gets called that parses the arguments
    *   4. OnArgumentsPassed gets called that can be overriden, in this function we add defaults if something was not specified in cmd args
    */

    class EngineConfiguration {
    public:
        EngineConfiguration();
        ~EngineConfiguration();

        void ParseArguments(int argc, char** argv);

        void SetResourcesPath(const std::string& path) { m_resourcesPath = path; }
        const std::string& GetResourcesPath() const { return m_resourcesPath; }

    private:
        cli::Arguments m_arguments;
        std::string m_resourcesPath;
    };
}
