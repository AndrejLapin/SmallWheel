#pragma once

#include "SmallWheel/Application.hpp"
#include "SmallWheel/EngineConfiguration.hpp"

extern swheel::Application* swheel::CreateApplication();

int main(int argc, char** argv)
{
    swheel::EngineConfiguration configuration;
    swheel::Application* app = swheel::CreateApplication();
    if (configuration.ParseArguments(argc, argv)) {
       app->InitialiseApplication(configuration);
       app->Run(); 
    }
    delete app;
}
