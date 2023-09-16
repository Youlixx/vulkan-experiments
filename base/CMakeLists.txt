file(GLOB BASE_SRC "*.cpp" "*.hpp" "*.h")
file(GLOB BASE_HEADERS "*.hpp" "*.h")

add_library(base ${BASE_SRC})
target_link_libraries(base Vulkan::Vulkan glfw)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
