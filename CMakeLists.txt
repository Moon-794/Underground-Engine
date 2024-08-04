cmake_minimum_required(VERSION 3.0.0)
project(UndergroundEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/)

add_executable(UndergroundEngine src/main.cpp
src/engine.cpp src/glad.c src/gametime.cpp src/gameObject.cpp
src/component.cpp src/scene.cpp src/scene.cpp src/mesh.cpp src/model.cpp)

target_include_directories(UndergroundEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(Assimp REQUIRED)
target_link_libraries(UndergroundEngine assimp::assimp ${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a)


