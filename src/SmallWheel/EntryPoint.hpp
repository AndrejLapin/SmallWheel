#pragma once

extern swheel::Application* swheel::CreateApplication();

int main(int argc, char** argv)
{
    auto app = swheel::CreateApplication();
    app->Run();
    delete app;
}