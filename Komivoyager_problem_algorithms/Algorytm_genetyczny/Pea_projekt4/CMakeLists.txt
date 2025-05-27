cmake_minimum_required(VERSION 3.29)
project(Pea_projekt4)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/Headers)

add_executable(Pea_projekt3 Sources/main.cpp
        Sources/main_switch.cpp
        Headers/main_switch.h
        Headers/load.h
        Sources/load.cpp
        Sources/genetic_algorithm.cpp
        Headers/genetic_algorithm.h
        Sources/quicksort.cpp
        Sources/measurements.cpp
        Headers/measurements.h
        Headers/nearest_neighbour.h
        Sources/neares_neighbour.cpp
)
