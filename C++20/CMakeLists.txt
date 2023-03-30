# 1.
cmake_minimum_required(VERSION 3.22.1)


# 4. 指定特性
set(CMAKE_CXX_STANDARD 23)      # C++23版本
set(CMAKE_CXX_EXTENSION OFF)    # 关闭扩展
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 如果C++20编译器不存在，停止配置

# 2.
project(C++20Features)

# 3.
ADD_SUBDIRECTORY(src)
