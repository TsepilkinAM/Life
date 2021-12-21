cmake_minimum_required(VERSION 3.14)
project(Life)
FIND_PACKAGE(SFML 2.5 COMPONENTS graphics window REQUIRED)
#include(FetchContent)

#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        release-1.10.0
#)
#FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

add_executable(Life Life.cpp Life.h Game.cpp Game.h main.cpp)
target_link_libraries(Life sfml-graphics sfml-window)

#enable_testing()
#include(GoogleTest)
#gtest_discover_tests(Life)




