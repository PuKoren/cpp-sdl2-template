#include "Display.h"

#include <iostream>

#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>
#include "VkBootstrap.h"

Display::Display()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::cerr << "Failed to initialize the SDL2 library\n";
    }

    window = SDL_CreateWindow("SDL2 Template",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              680, 480,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        return;
    }

    vkb::InstanceBuilder builder;
    auto inst_ret = builder.set_app_name("Example Vulkan Application")
                        .request_validation_layers()
                        .use_default_debug_messenger()
                        .build();
    if (!inst_ret)
    {
        std::cerr << "Failed to create Vulkan instance. Error: " << inst_ret.error().message() << "\n";
        return;
    }

    vkbInstance = inst_ret.value();

    if (!SDL_Vulkan_CreateSurface(window, vkbInstance.instance, &surface))
    {
        std::cerr << "Vulkan surface creation failed\n";
        return;
    }

    vkb::PhysicalDeviceSelector selector{vkbInstance};
    auto phys_ret = selector.set_surface(surface)
                        .set_minimum_version(1, 1) // require a vulkan 1.1 capable device
                        .require_dedicated_transfer_queue()
                        .select();
    if (!phys_ret)
    {
        std::cerr << "Failed to select Vulkan Physical Device. Error: " << phys_ret.error().message() << "\n";
        return;
    }

    vkb::DeviceBuilder device_builder{phys_ret.value()};
    auto dev_ret = device_builder.build();
    if (!dev_ret)
    {
        std::cerr << "Failed to create Vulkan device. Error: " << dev_ret.error().message() << "\n";
        return;
    }
    vkbDevice = dev_ret.value();

    auto graphics_queue_ret = vkbDevice.get_queue(vkb::QueueType::graphics);
    if (!graphics_queue_ret)
    {
        std::cerr << "Failed to get graphics queue. Error: " << graphics_queue_ret.error().message() << "\n";
        return;
    }
    graphicsQueue = graphics_queue_ret.value();

    auto present_queue_ret = vkbDevice.get_queue(vkb::QueueType::present);
    if (!present_queue_ret.has_value())
    {
        std::cerr << "failed to get present queue: " << present_queue_ret.error().message() << "\n";
        return;
    }
    presentQueue = present_queue_ret.value();

    vkb::SwapchainBuilder swapchain_builder{vkbDevice};
    auto swap_ret = swapchain_builder.set_old_swapchain(vkbSwapchain).build();
    if (!swap_ret)
    {
        std::cerr << swap_ret.error().message() << " " << swap_ret.vk_result() << "\n";
        return;
    }
    vkb::destroy_swapchain(vkbSwapchain);
    vkbSwapchain = swap_ret.value();

    ready = true;
};

Display::~Display()
{
    vkb::destroy_swapchain(vkbSwapchain);
    vkb::destroy_device(vkbDevice);
    vkb::destroy_surface(vkbInstance, surface);
    vkb::destroy_instance(vkbInstance);

    SDL_Vulkan_UnloadLibrary();
    SDL_DestroyWindow(window);
    SDL_Quit();
};

bool Display::isReady()
{
    return ready;
}
