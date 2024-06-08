#pragma once

#include "Result.hpp"

namespace swheel::cli {
    class Argument {
    public:
        enum class Type {
            NONE,
            STRING,
            BOOL
        };
    public:
        Argument() = default;
        Argument(std::string longName, std::string shortName,
                std::string helperInput, std::string helperExplanation,
                void* dataField, Type type);
        ~Argument() {}

        void PrintHelp();
        Result<bool, std::string> HandleArgument(int argc, char** argv, int current);

    private:
        const std::string m_long;
        const std::string m_short;
        const std::string m_helperInput;
        const std::string m_helperExplanation;
        void* const m_dataField = nullptr;
        Type m_type = Type::NONE;
        bool m_handled = false;
    };

    class Arguments {
    public:
        // Maybe I dont need default constructor? Or maybe I do?
        // Arguments() = default;
        Arguments(std::string programName, bool defaultHelpArg = true);
        ~Arguments();

        // TODO: create function to add multiple arguments at once
        void AddArgument(Argument&& argument);
        void ParseArguments(int argc, char** argv);

    private:
        void PrintHelp();

    private:
        std::string m_executableName;
        std::string m_programName;
        // TODO: implement dynamic array with managed memory for performance imrpovements
        std::vector<std::optional<Argument>> m_arguments;
        bool m_showHelp = false;
    };
}
