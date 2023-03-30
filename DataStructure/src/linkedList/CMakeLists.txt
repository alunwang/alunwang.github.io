
# 定义源文件列表
set(SRC_LIST linkedList.cpp)

set(CMAKE_BUILD_TYPE Debug)

# 指定生成目标 目标名字随便写；${SRC_LIST}代表前面定义的源文件列表变量
ADD_EXECUTABLE(linkedList ${SRC_LIST})