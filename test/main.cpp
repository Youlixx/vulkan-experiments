#include "../base/Window.hpp"

int main() {
    vkexp::Window window{1280, 720, "window!!"};

    while (!window.shouldClose()) {
        glfwPollEvents();
    }

    return 0;
}
