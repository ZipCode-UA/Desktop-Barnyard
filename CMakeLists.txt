cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project(DesktopBarnyard LANGUAGES CXX)

# Include GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Paths to submodules
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/glfw)

# Add GLFW as a submodule
add_subdirectory(${GLFW_DIR})

# ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw GL)

# Add OpenGL support for Windows or Linux/macOS
if(WIN32)
    target_link_libraries(imgui PRIVATE glfw opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PRIVATE glfw GL)
endif()

# Main executable
add_executable(DesktopBarnyard opengl_glfw_example.cpp)
target_link_libraries(DesktopBarnyard PRIVATE imgui glfw)
