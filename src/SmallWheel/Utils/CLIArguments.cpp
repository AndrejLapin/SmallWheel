#include "swpch.hpp"
#include "CLIArguments.hpp"

#include "SmallWheel/Core.hpp"

namespace swheel::cli {
    Argument::Argument(std::string longName, std::string shortName,
        std::string helperInput, std::string helperExplanation,
        void* dataField, Type type): 
        m_long("--" + longName), m_short("-" + shortName), 
        m_helperInput(helperInput), m_helperExplanation(helperExplanation),
        m_dataField(dataField), m_type(type) {
    }

    void Argument::PrintHelp() {
        SW_ASSERT_LOG(m_type != Type::NONE , "Something went wrong! Unconfigured argument ended up in arguments!");
        //TODO: there should be some kind of indentation counter before m_helperExplanation
        std::cout << " " << m_short << ", " << m_long << " " << m_helperInput << " " << m_helperExplanation << "\n";
    }

    Result<bool, std::string> Argument::HandleArgument(int argc, char** argv, int current) {
        SW_ASSERT_LOG(m_type != Type::NONE , "Something went wrong! Unconfigured argument ended up in arguments!");

        if (m_long.find(argv[current]) == std::string::npos && (m_short.empty() || m_short.find(argv[current]) == std::string::npos)) {
            return Result<bool, std::string>::success(false);
        }

        if (m_handled) {
            return Result<bool, std::string>::error("Duplicate argument: " + m_long + "\n");
        }

        switch (m_type) {
        case Type::STRING: {
            // do a check first
            if (current + 1 == argc ||
            argv[current + 1][0] == '-') {
                return Result<bool, std::string>::error(m_helperInput + " was not provided for argument " + m_long + "\n");
            }
            auto& string =*reinterpret_cast<std::string*>(m_dataField);
            string = argv[++current];
        }break;
        case Type::BOOL: {
            auto& boolean = *reinterpret_cast<bool*>(m_dataField);
            boolean = true;
        }break;
        default: {
            SW_ASSERT_LOG(false, "Unknown argument type!");
            return Result<bool, std::string>::error("Unknown argument type!\n");
        }
        }
        m_handled = true;
        return Result<bool, std::string>::success(true);
    }

    Arguments::Arguments(std::string programName, bool defaultHelpArg) {
        m_programName = programName;
        m_arguments.reserve(1 + defaultHelpArg);
        AddArgument(Argument("help", "h", "", "Show this help message", &m_showHelp, Argument::Type::BOOL));
    }

    Arguments::~Arguments() {}

    void Arguments::AddArgument(Argument&& argument) {
        if (m_arguments.size() == m_arguments.capacity()) {
            m_arguments.reserve(std::ceil(m_arguments.size() * 1.5f));
        }
        m_arguments.emplace_back(std::move(argument));
    }

    void Arguments::ParseArguments(int argc, char** argv) {
        m_executableName = argv[0];
        if (argc < 2) {
            return;
        }
        std::string errorMessage;
        m_showHelp = false;
        for (int i = 1; i < argc; ++i) {
            bool handled = false;
            for (auto rit = m_arguments.rbegin(); rit != m_arguments.rend(); ++rit) {
                SW_ASSERT_LOG(rit->has_value(), "Argument has no value!");
                Result<bool, std::string> result = rit->value().HandleArgument(argc, argv, i);
                if (!result.isSuccess()) {
                    errorMessage += result.getError();
                    continue;
                }
                if (result.getResult()) {
                    handled = true;
                    break;
                }
            }
            if (!handled) {
                m_showHelp = true;
                std::stringstream error;
                error << "Unknown option " << argv[i] << "\n";
                errorMessage += error.str();
            }
        }
        if (!errorMessage.empty()) {
            std::cerr << errorMessage;
        }
        if (m_showHelp) {
            PrintHelp();
        }
    }

    void Arguments::PrintHelp() {
        std::cout << "Usage: ";
        if (m_programName.empty()) {
            std::cout << "SmallWheel engine program (" << m_executableName << ")";
        } else {
            std::cout << m_programName;
        }
        std::cout << " [options]\n"
        << "Options: \n";
        for (auto rit = m_arguments.rbegin(); rit != m_arguments.rend(); ++rit) {
            SW_ASSERT_LOG(rit->has_value(), "Argument has no value!");
            rit->value().PrintHelp();
        }
    }
}
