cmake_minimum_required(VERSION 3.14)
project(StudentuPrograma VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(programa
    main1.cpp
    funkcijos1.cpp
)
target_include_directories(programa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(testai
    testas_gtest.cpp
)
target_link_libraries(testai GTest::gtest_main)
target_include_directories(testai PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(testai)
