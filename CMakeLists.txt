cmake_minimum_required(VERSION 3.10)
project(SafeQueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(safeQueue main.cpp safeQueue.cpp)

target_include_directories(safeQueue PRIVATE .)

target_link_libraries(safeQueue PRIVATE Threads::Threads)
