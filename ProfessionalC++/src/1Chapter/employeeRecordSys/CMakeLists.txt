
# 定义源文件列表
set(SRC_LIST
    employeeRecord.cpp
    database.cpp
    employeeTest.cpp
    databaseTest.cpp
    interface.cpp
)

# 指定最终生成的可执行文件的路径
# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# 指定生成目标 目标名字随便写；${SRC_LIST}代表前面定义的源文件列表变量
# ADD_EXECUTABLE(employeeRecordSys ${SRC_LIST})