cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include(CTest)
enable_testing()

link_directories(lib/)
include_directories(include/)
add_executable(Test src/main.cpp src/glad.c 
src/ImGUI/imgui_demo.cpp src/ImGUI/imgui_draw.cpp src/ImGUI/imgui_impl_glfw.cpp src/ImGUI/imgui_impl_opengl3.cpp src/ImGUI/imgui_tables.cpp src/ImGUI/imgui_widgets.cpp src/ImGUI/imgui.cpp
src/mesh.cpp src/Player.cpp src/Model.cpp)

target_link_libraries(Test PRIVATE libglfw3dll.a assimp-vc143-mt.lib)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
