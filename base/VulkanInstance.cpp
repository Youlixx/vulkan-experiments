#include "VulkanInstance.hpp"

#include <stdexcept>
#include <cstring>

using namespace vkexp;

VulkanInstance::VulkanInstance(Window& window, VkAllocationCallbacks* allocator): 
    _window{ window }, 
    _allocator{ allocator } 
{
#ifdef VKEXP_DEBUG
    setupInstance("Vulkan Application", "No Engine", {"VK_LAYER_KHRONOS_validation"});
#else
    setupInstance("Vulkan Application", "No Engine", {});
#endif
}

VulkanInstance::VulkanInstance(
    Window& window, 
    const std::vector<const char*>& requiredLayers, 
    VkAllocationCallbacks* allocator
): 
    _window{ window }, 
    _allocator{ allocator } 
{
    setupInstance("Vulkan Application", "No Engine", requiredLayers);
}

VulkanInstance::VulkanInstance(
    Window& window, 
    const char* applicationName,
    const char* engineName,
    const std::vector<const char*>& requiredLayers, 
    VkAllocationCallbacks* allocator
): 
    _window{ window }, 
    _allocator{ allocator } 
{
    setupInstance(applicationName, engineName, requiredLayers);
}

VulkanInstance::~VulkanInstance() {
    vkDestroySurfaceKHR(_instance, _surface, _allocator);
    vkDestroyInstance(_instance, _allocator);
}

std::vector<VkLayerProperties> VulkanInstance::getAvailableLayers() {
    uint32_t availableLayerCount;
    vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);

    std::vector<VkLayerProperties> availabeLayers{ availableLayerCount };
    vkEnumerateInstanceLayerProperties(&availableLayerCount, availabeLayers.data());

    return availabeLayers;
}

void VulkanInstance::setupInstance(
    const char* applicationName,
    const char* engineName,
    const std::vector<const char*>& requiredLayers
) {
    if (!checkRequiredLayers(requiredLayers)) {
        throw std::runtime_error("The required validation layers are not available");
    }

    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = applicationName;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    applicationInfo.pEngineName = engineName;
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;

    uint32_t enabledExtensionCount;
    const char** enabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledExtensionCount = enabledExtensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = enabledExtensionNames;
    instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
    instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();

    if (vkCreateInstance(&instanceCreateInfo, _allocator, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create the Vulkan instance");
    }

    _window.createWindowSurface(_instance, &_surface);
}

bool VulkanInstance::checkRequiredLayers(const std::vector<const char*>& requiredLayers) const {
    const std::vector<VkLayerProperties> availabeLayers = getAvailableLayers();

    for (const auto& requiredLayer : requiredLayers) {
        bool isRequiredLayerAvailable = false;

        for (const auto& layer : availabeLayers) {
            if (strcmp(layer.layerName, requiredLayer) == 0) {
                isRequiredLayerAvailable = true;
                break;
            }
        }

        if (!isRequiredLayerAvailable) {
            return false;
        }
    }

    return true;
}