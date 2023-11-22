cmake_minimum_required(VERSION 3.0.0)

add_library(AssetImporter mesh.cpp model.cpp)
target_include_directories(AssetImporter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/AssetImporter)
target_include_directories(AssetImporter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)