#pragma once

#ifdef SW_PLATFORM_WINDOWS

extern swheel::Application* swheel::CreateApplication();

int main(int argc, char** argv)
{
    auto app = swheel::CreateApplication();
    app->Run();
    delete app;
}

#endif // SW_PLATFORM_WINDOWS