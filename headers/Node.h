#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>

class Node
{
public:
    void update(float deltaTime, SDL_Event* event);
    void draw(SDL_Renderer* renderer);
};

#endif