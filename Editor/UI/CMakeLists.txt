cmake_minimum_required(VERSION 3.0.0)

add_library(IMGUI imgui.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp)
target_include_directories(IMGUI PUBLIC ../../include/Editor/UI/)