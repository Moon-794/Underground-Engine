cmake_minimum_required(VERSION 3.0.0)
project(Underground VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

link_directories(lib/)
include_directories(include/)

add_executable(Underground src/main.cpp src/glad.c)
target_link_libraries(Underground "libglfw3.a")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
