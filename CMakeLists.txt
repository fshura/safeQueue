cmake_minimum_required(VERSION 3.10)
project(SafeQueue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(safeQueue src/main.cpp src/safeQueue.cpp)

target_link_libraries(safeQueue PRIVATE Threads::Threads)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    set(GTEST_LIBRARY_DIR /usr/lib64)
    set(GTEST_INCLUDE_DIR /usr/include)

    add_executable(run_tests tests/test_main.cpp src/safeQueue.cpp)
    target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIR})
    target_link_libraries(run_tests PRIVATE 
        ${GTEST_LIBRARY_DIR}/libgtest.a
        ${GTEST_LIBRARY_DIR}/libgtest_main.a
        pthread
    )
    add_test(NAME MyTests COMMAND run_tests)
endif()
