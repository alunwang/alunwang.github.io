# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.22.1)

# 项目工程名
project (ProfessionalC++ LANGUAGES CXX) # 使用C++编译器

message(STATUS "root This is ROOT dir " ${PROJECT_SOURCE_DIR})

# 编译选项
set(CMAKE_CXX_STANDARD 20)      # C++20版本
set(CMAKE_CXX_EXTENSION OFF)    # 关闭扩展
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 如果C++20编译器不存在，停止配置
# set(CMAKE_CXX_FLAGS "-fmodules-ts")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
#   "${compiler_flags_for_module_map} -fmodule-mapper=<MODULE_MAP_FILE>")

# 指定的头文件目录
INCLUDE_DIRECTORIES(include)

# 添加子目录
ADD_SUBDIRECTORY(src)