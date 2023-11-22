cmake_minimum_required(VERSION 3.0.0)

add_library(ECS scene.cpp gameObject.cpp component.cpp)
target_include_directories(ECS PUBLIC ../../include/ECS)