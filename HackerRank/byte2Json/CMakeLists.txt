cmake_minimum_required(VERSION 3.22.1)

set(PRJ_NAME byte2Json)
project(${PRJ_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20) # C++20

# Header file directory
INCLUDE_DIRECTORIES(include)

# 
ADD_SUBDIRECTORY(src)