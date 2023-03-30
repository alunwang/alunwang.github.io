#include <thread>
#include "simpleLogger.h"

void test_logger(int n)
{
    logging::Logger::logDebug("Logging message %d", n);
}
void test_singletoLogger(int n)
{
    // logging::SingletonLogger& singleton = logging::SingletonLogger::getLogger();
    // singleton.logDebug("Logging message %d", n);
    LOG_DEBUG("Logging message %d", n);
}
int main()
{
    int n = 0;
#if 0
    logging::Logger::setDefaultLevel(logging::Level::TRACE);

    logging::Logger::enableLogToFile();
    std::thread threads[10];
    for (int i {0}; i<10; ++i) {
        threads[i] = std::thread {test_logger, i};
    }
    for (auto& thread : threads) {
        thread.join();
    }
    logging::Logger::logTrace("Logging message %d", n);
    logging::Logger::logDebug("Logging message %d", n);
    logging::Logger::logInfo("Logging message %d", n);
    logging::Logger::logWarn("Logging message %d", n);
    logging::Logger::logError("Logging message %d", n);
    logging::Logger::logFatal("Logging message %d", n);

    logging::Logger::disableLogToFile();
#else
    logging::SingletonLogger::setDefaultLevel(logging::Level::TRACE);

    logging::SingletonLogger::enableLogToFile();
    std::thread threads[10];
    for (int i {0}; i<10; ++i) {
        threads[i] = std::thread {test_singletoLogger, i};
    }
    for (auto& thread : threads) {
        thread.join();
    }
    LOG_TRACE("Logging message %d", n);
    LOG_DEBUG("Logging message %d", n);
    LOG_INFO("Logging message %d", n);
    LOG_WARN("Logging message %d", n);
    LOG_ERROR("Logging message %d", n);
    LOG_FATAL("Logging message %d", n);
#endif
    return 0;
}