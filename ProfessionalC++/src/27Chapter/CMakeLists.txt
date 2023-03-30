set(SRC_LIST multiThread.cpp)
set(SRC logger.cpp)
set(SRC1 simpleLogger.cpp)
set(SRC2 loggerWithBuffer.cpp)


ADD_EXECUTABLE(multiThread ${SRC_LIST})
ADD_EXECUTABLE(logger ${SRC})
ADD_EXECUTABLE(simpleLogger ${SRC1})
ADD_EXECUTABLE(loggerWithBuffer ${SRC2})