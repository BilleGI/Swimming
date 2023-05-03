cmake_minimum_required(VERSION 3.5)

add_executable(untitled3 main.cpp ${MY_INCLUDE_DIR}/swimmer.h swimmer.cpp)

target_include_directories(untitled3 PUBLIC ${MY_INCLUDE_DIR})
