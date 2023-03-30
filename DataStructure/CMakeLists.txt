# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.22.1)
# 项目工程名
project (DataStructure)

message(STATUS "root This is ROOT dir " ${PROJECT_SOURCE_DIR})


# 编译选项
# set(CMAKE_CXX_FLAGS "-std=c++20 -fmodules-ts")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fmodules-ts")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
#   "${compiler_flags_for_module_map} -fmodule-mapper=<MODULE_MAP_FILE>")

# 添加子目录
ADD_SUBDIRECTORY(src)