#include "../base/Window.hpp"
#include "../base/VulkanInstance.hpp"

#include <iostream>

int main() {
    auto layers = vkexp::VulkanInstance::getAvailableLayers();

    std::cout << "Available layers" << std::endl;
    for (auto& layer : layers) {
        std::cout << layer.layerName << " -> " << layer.description << std::endl;
    }

    vkexp::Window window{1280, 720, "window!!"};
    vkexp::VulkanInstance instance{window};

    while (!window.shouldClose()) {
        glfwPollEvents();
    }

    return 0;
}
