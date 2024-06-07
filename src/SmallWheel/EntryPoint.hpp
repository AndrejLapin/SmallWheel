#pragma once

#include "SmallWheel/Application.hpp"
#include "SmallWheel/EngineConfiguration.hpp"

extern swheel::Application* swheel::CreateApplication();

int main(int argc, char** argv)
{
    swheel::EngineConfiguration configuration;
    swheel::Application* app = swheel::CreateApplication();
    configuration.ParseArguments(argc, argv);
    app->ConfigureEngine(configuration);
    app->Run();
    delete app;
}
