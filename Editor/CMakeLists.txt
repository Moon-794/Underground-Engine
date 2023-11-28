cmake_minimum_required(VERSION 3.0.0)
project(Editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/Editor)

add_subdirectory(ProjectLoader)
add_subdirectory(UI)

add_executable(UndergroundEditor src/main.cpp)
target_include_directories(UndergroundEditor PUBLIC include/ ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

target_link_directories(UndergroundEditor PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(UndergroundEditor libglfw3dll.a Core ProjectLoader IMGUI)