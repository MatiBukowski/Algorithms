cmake_minimum_required(VERSION 3.29)
project(Pea_projekt3)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/Headers)

add_executable(Pea_projekt3 Sources/main.cpp
        Sources/load.cpp
        Headers/load.h
        Sources/tabu_search.cpp
        Headers/tabu_search.h
        Sources/neares_neighbour.cpp
        Headers/nearest_neighbour.h
        Sources/main_switch.cpp
        Headers/main_switch.h
        Sources/quicksort.cpp
        Headers/quicksort.h
        Sources/motion_rate_function.cpp
        Headers/motion_rate_function.h
        Sources/moves.cpp
        Headers/moves.h)
