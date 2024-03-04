#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <vulkan/vulkan.hpp>
#include "VkBootstrap.h"

class Display
{
public:
    Display();
    ~Display();
    bool isReady();

private:
    SDL_Window *window;
    VkSurfaceKHR surface;
    vkb::Instance vkbInstance;
    vkb::Device vkbDevice;
    vkb::Swapchain vkbSwapchain;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    bool ready = false;
};

#endif