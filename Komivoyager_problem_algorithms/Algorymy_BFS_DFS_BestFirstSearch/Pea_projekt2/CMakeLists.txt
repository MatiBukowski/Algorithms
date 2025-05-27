cmake_minimum_required(VERSION 3.29)
project(Pea_projekt2)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${PROJECT_SOURCE_DIR}/Headers)
add_executable(Pea_projekt2 Sources/main.cpp
        Sources/main_switch.cpp
        Headers/main_switch.h
        Sources/load.cpp
        Headers/load.h
        Sources/generate.cpp
        Headers/generate.h
        Sources/best_first_search.cpp
        Headers/best_first_search.h
        Headers/node.h
        Sources/node.cpp
        Headers/breadth_first_search.h
        Sources/breath_first_search.cpp
        Sources/depth_first_search.cpp
        Headers/depth_first_search.h
        Sources/best_first_search_sym.cpp
        Headers/best_first_search_sym.h
        Sources/depth_first_search_sym.cpp
        Headers/depth_first_search_sym.h
        Sources/breadth_first_search_sym.cpp
        Headers/breadth_first_search_sym.h
)
