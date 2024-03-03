#include "Application.h"

Application::Application()
{
    running = true;
}

bool Application::isRunning()
{
    return running;
}

void Application::update(float delta)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Application::draw(SDL_Renderer *renderer)
{
}
