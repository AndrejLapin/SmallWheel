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

        bool ParseArguments(int argc, char** argv);

        void SetWindowName(const std::string& name) { m_windowName = name; }
        const std::string& GetWindowName() const { return m_windowName; }

        void SetWindowSize(int widht, int height) { m_windowSize = {widht, height}; }
        const std::pair<int, int>& GetWindowSize() { return m_windowSize; }

        void SetResourcesPath(const std::string& path) { m_resourcesPath = path; }
        const std::string& GetResourcesPath() const { return m_resourcesPath; }

    private:
        cli::Arguments m_arguments;

        /* ====== Configuration ====== */
        std::string m_windowName;
        std::pair<int, int> m_windowSize = {0,0};
        std::string m_resourcesPath;
    };
}
