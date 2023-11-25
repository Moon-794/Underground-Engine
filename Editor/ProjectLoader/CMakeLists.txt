cmake_minimum_required(VERSION 3.0.0)

add_library(ProjectLoader projectLoader.cpp)
target_include_directories(ProjectLoader PUBLIC ../../include/Editor/ProjectLoader)