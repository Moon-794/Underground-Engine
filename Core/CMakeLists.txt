cmake_minimum_required(VERSION 3.0.0)
project(Engine_Core)

add_subdirectory(ECS)
add_subdirectory(GameTime)
add_subdirectory(AssetImporter)

add_library(Core STATIC src/engine.cpp src/glad.c)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/Engine/)
target_include_directories(Core PUBLIC Components)

set(GLFW_INCLUDE_DIRS /usr/include) 
set(GLFW_LIBRARIES /usr/lib/libglfw.so.3.3)

find_package(assimp REQUIRED)
target_link_directories(Core PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(Core GameTime ECS AssetImporter assimp::assimp ${GLFW_LIBRARIES})
