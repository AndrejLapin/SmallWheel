#pragma once

#include <string>

namespace swheel {
    class Event;

    class Window {
    public:
        Window(const std::string& title, int width, int height): m_title(title), m_width(width), m_height(height) {}
        virtual ~Window() = default;

        virtual void OnEvent(Event& event) = 0;
        virtual bool IsClosed() const = 0;

    protected:
        std::string m_title;
        int m_width;
        int m_height;
    };
}
