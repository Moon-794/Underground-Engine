cmake_minimum_required(VERSION 3.0.0)
project(Engine_Core)

add_subdirectory(ECS)
add_subdirectory(GameTime)
add_subdirectory(AssetImporter)

add_library(Core STATIC src/engine.cpp src/glad.c)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/Engine/)
target_include_directories(Core PUBLIC Components)

find_package(Assimp)
target_link_directories(Core PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(Core GameTime ECS AssetImporter assimp::assimp libglfw3dll.a)
