cmake_minimum_required(VERSION 3.2)

# project(test)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


add_definitions(-std=c++11)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})
# 显示GTest路径
MESSAGE(STATUS "GTEST_INCLUDE_DIRS" ${GTEST_INCLUDE_DIRS})
 

add_executable(test main.cpp mylist.h)

target_link_libraries(test ${GTEST_BOTH_LIBRARIES} pthread)

