#ifndef __BASE_VULKAN_INSTANCE_HPP__
#define __BASE_VULKAN_INSTANCE_HPP__

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanBase.hpp"
#include "Window.hpp"

namespace vkexp
{
class VulkanInstance {
public:
    VulkanInstance(Window& window, VkAllocationCallbacks* allocator = nullptr);

    VulkanInstance(
        Window& window, 
        const std::vector<const char*>& requiredLayers, 
        VkAllocationCallbacks* allocator = nullptr
    );

    VulkanInstance(
        Window& window, 
        const char* applicationName,
        const char* engineName,
        const std::vector<const char*>& requiredLayers, 
        VkAllocationCallbacks* allocator = nullptr
    );
    
    ~VulkanInstance();

public:
    static std::vector<VkLayerProperties> getAvailableLayers();

private:
    void setupInstance(
        const char* applicationName,
        const char* engineName,
        const std::vector<const char*>& requiredLayers
    );

    bool checkRequiredLayers(const std::vector<const char*>& requiredLayers) const;

private:
    Window& _window;

    VkInstance _instance;
    VkSurfaceKHR _surface;

    VkAllocationCallbacks* _allocator;
};
}

#endif