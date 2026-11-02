cmake_minimum_required(VERSION 3.16)
project(zykovlab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(zykovlab2
    main.cpp
    Pipe.cpp
    CompressorStation.cpp
    Storage.cpp
    Search.cpp
)
