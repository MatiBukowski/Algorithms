cmake_minimum_required(VERSION 3.29)
project(Pea_projekt1)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/Headers)
add_executable(Pea_projekt1 Sources/main.cpp
        Sources/main_menu.cpp
        Headers/main_menu.h
        Sources/load.cpp
        Headers/load.h
        Sources/generate.cpp
        Headers/generate.h
        Sources/algorithm_menu.cpp
        Headers/algorithm_menu.h
        Sources/Nearest_neighbour.cpp
        Headers/nearest_neighbour.h
        Sources/complete_review.cpp
        Headers/complete_review.h
        Sources/random_algorithm.cpp
        Headers/random_algorithm.h)
