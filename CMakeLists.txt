cmake_minimum_required(VERSION 3.9.1)
project(BetaSim)
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
include_directories(BetaSim PUBLIC include)
add_executable(BetaSim main.cpp src/electron.cpp src/globals.cpp src/random_distribution.cpp src/simulation.cpp)