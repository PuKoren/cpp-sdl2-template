#include <chrono>
#include <iostream>

#include "Display.h"
#include "Application.h"

int main()
{
    Display* display = new Display();

    if (!display->isReady()) {
        std::cout << "Something went wrong initializing display, exiting\n";
        return 1;
    }

    Application* app = new Application();

    auto lastRunAt = std::chrono::high_resolution_clock::now();

    while (app->isRunning())
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(now - lastRunAt).count();
        lastRunAt = now;

        app->update(deltaTime);
        app->draw();
    }

    delete app;
    delete display;

    return 0;
}
