cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include(CTest)
enable_testing()

link_directories(lib/)
include_directories(include/)
add_executable(Test src/main.cpp src/glad.c)

target_link_libraries(Test "libglfw3.a")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
