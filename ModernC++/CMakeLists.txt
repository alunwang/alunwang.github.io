# 1. CMake 最低版本号要求
cmake_minimum_required (VERSION 3.22.1)

# 2. 项目工程名
# project (modernC++App)
project(modernC++App LANGUAGE CXX)  # 使用C++编译器

message(STATUS "root This is ROOT dir " ${PROJECT_SOURCE_DIR})

# 3. 添加子目录
ADD_SUBDIRECTORY(src)

# 4. 指定特性
set(CMAKE_CXX_STANDARD 20)      # C++20版本
set(CMAKE_CXX_EXTENSION OFF)    # 关闭扩展
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 如果C++20编译器不存在，停止配置