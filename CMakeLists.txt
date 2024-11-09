cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project(DesktopBarnyard LANGUAGES CXX)

add_executable(DesktopBarnyard src/main.cpp)
set_target_properties(DesktopBarnyard PROPERTIES OUTPUT_NAME "Desktop Barnyard")

add_subdirectory(include)
add_subdirectory(src)

target_link_libraries(DesktopBarnyard PRIVATE src)
target_link_options(DesktopBarnyard PRIVATE -mwindows)