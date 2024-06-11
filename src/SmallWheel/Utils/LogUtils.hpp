#pragma once

namespace swheel::log {
    template<typename... Args>
    void Info(Args&&... args) {
        (std::cout << ... << args) << "\n";
    }

    template<typename... Args>
    void Error(Args&&... args) {
        (std::cerr << ... << args) << "\n";
    }
}
