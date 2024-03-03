#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>

#include "Application.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Template",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Application* app = new Application();

    auto lastRunAt = std::chrono::high_resolution_clock::now();

    while (app->isRunning())
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(now - lastRunAt).count();
        lastRunAt = now;

        app->update(deltaTime);

        SDL_RenderClear(renderer);
        app->draw(renderer);
        SDL_RenderPresent(renderer);
    }

    delete app;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
