cmake_minimum_required(VERSION 3.0.0)

add_library(GameTime gameTime.cpp)
target_include_directories(GameTime PUBLIC ../../include/Engine/GameTime/)