#include "Window.hpp"

#include <stdexcept>

using namespace vkexp;

Window::Window(int width, int height, const char* title) {
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("Unable to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

Window::~Window() {
    glfwDestroyWindow(_windowHandle);
    glfwTerminate();
}

void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) const {
    if (glfwCreateWindowSurface(instance, _windowHandle, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create surface");
    }
}

void Window::getFrameBufferSize(int& width, int& height) const {
    glfwGetFramebufferSize(_windowHandle, &width, &height);
}

bool Window::isMinimized() const {
    return glfwGetWindowAttrib(_windowHandle, GLFW_ICONIFIED) == VK_TRUE;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(_windowHandle) || glfwGetKey(_windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}
