cmake_minimum_required(VERSION 3.0.0)
project(Editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/Editor)
add_subdirectory(UI)

add_executable(UndergroundEditor src/main.cpp)
target_include_directories(UndergroundEditor PUBLIC include/ ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

set(GLFW_INCLUDE_DIRS /usr/include)
set(GLFW_LIBRARIES /usr/lib/libglfw.so.3.3)


target_link_directories(UndergroundEditor PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(UndergroundEditor ${GLFW_LIBRARIES} Core IMGUI)
