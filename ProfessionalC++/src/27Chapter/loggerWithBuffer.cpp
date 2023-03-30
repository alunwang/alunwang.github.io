#include <thread>
#include <vector>
#include "loggerWithBuffer.h"


logging::Logger logger;

#define LOG_TRACE(message, ...) (logger.logTrace(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_DEBUG(message, ...) (logger.logDebug(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_INFO(message, ...) (logger.logInfo(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_WARN(message, ...) (logger.logWarn(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_ERROR(message, ...) (logger.logError(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_FATAL(message, ...) (logger.logFatal(__LINE__, __FILE__, message, __VA_ARGS__))

void logMessages(int n)
{
    LOG_DEBUG("Logging message %d", n);
}

int main()
{
    int n = 0;

    logger.setDefaultLevel(logging::Level::TRACE);

    logger.enableLogToFile();
    std::thread threads[10];
    // std::vector<std::thread> threads;
    for (int i {0}; i<10; ++i) {
        threads[i] = std::thread {logMessages, i};
        // threads.emplace_back(logMessages, i, std::ref(logger));
    }
    for (auto& t : threads) {
        t.join();
    }
    LOG_TRACE("Logging message %d", n);
    LOG_DEBUG("Logging message %d", n);
    LOG_INFO("Logging message %d", n);
    LOG_WARN("Logging message %d", n);
    LOG_ERROR("Logging message %d", n);
    LOG_FATAL("Logging message %d", n);

    return 0;
}