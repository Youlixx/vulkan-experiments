#ifndef __BASE_WINDOW_HPP__
#define __BASE_WINDOW_HPP__

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vkexp
{
class Window { 
public:
    Window(int width, int height, const char* title);
    ~Window();

public:
    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) const;
    void getFrameBufferSize(int& width, int& height) const;

    bool isMinimized() const;
    bool shouldClose() const;

    GLFWwindow* getWindowHandle() const { return _windowHandle; }

private:
    GLFWwindow* _windowHandle;
};
}

#endif