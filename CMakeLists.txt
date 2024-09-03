cmake_minimum_required(VERSION 3.8)
project(UndergroundEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/)

set(SRC_FILES src/glad.c
src/engine.cpp src/gametime.cpp src/gameObject.cpp
src/component.cpp src/scene.cpp src/scene.cpp src/mesh.cpp src/model.cpp)

option(BUILD_LIBRARY "Build a static library of the engine" OFF)

if(BUILD_LIBRARY)
    add_library(UndergroundEngine ${SRC_FILES})
else()
    add_executable(UndergroundEngine src/main.cpp ${SRC_FILES})
endif()

target_include_directories(UndergroundEngine PRIVATE ${CMAKE_SOURCE_DIR}/include $ENV{VCPKG_ROOT}/installed/x64-windows/include)

find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(UndergroundEngine OpenGL::GL glm::glm-header-only assimp::assimp glfw)


