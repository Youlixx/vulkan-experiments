cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

set(NAME vulkan-experiments)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

# Looks for the Vulkan and GLFW3 packages
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(base)
add_subdirectory(test)
