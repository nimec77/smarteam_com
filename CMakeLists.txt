cmake_minimum_required(VERSION 3.19)
project(smarteam_com)

set(CMAKE_CXX_STANDARD 20)

include_directories(smarteam)

set(SRC_PROVIDERS smarteam/data/providers/smarteam_provider.cpp smarteam/data/providers/engine_provider.cpp)

set(SRC_LIST ${SRC_PROVIDERS} main.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})