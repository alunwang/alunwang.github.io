#pragma once

#include <iostream>
#include <mutex>
#include <ctime>
#include <string>
#include <queue>
#include <fstream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <format>

namespace logging
{

enum class Level {
    TRACE=0, DEBUG, INFO, WARN, ERROR, FATAL
};

const char* enum2String[] = { // enum->字符串映射，enum转换为相应字符串
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

class Logger {
    public:
        Logger();
        virtual ~Logger();
        Logger(const Logger& logger) = delete;
        Logger& operator=(const Logger& logger) = delete;

        void setDefaultLevel(Level level);
        void enableLogToFile(const char*);

        template <typename... Args>
        void logTrace(const int line, const char* source, const char* message, Args... args);
        template <typename... Args>
        void logDebug(const int line, const char* source, const char* message, Args... args);
        template <typename... Args>
        void logInfo(const int line, const char* source, const char* message, Args... args);
        template <typename... Args>
        void logWarn(const int line, const char* source, const char* message, Args... args);
        template <typename... Args>
        void logError(const int line, const char* source, const char* message, Args... args);
        template <typename... Args>
        void logFatal(const int line, const char* source, const char* message, Args... args);
        // 由后台thread执行，处理日志记录
        void processEntries();
        // Helper method to process a queue of entries
        void processEntriesHelper(std::queue<std::string>& queue) const;
    private:
        template <typename... Args>
        void log(const int line, const char* source, Level level, const char* message, Args... args);
    private:
        // Boolean telling the background thread to terminate
        bool m_exit {false};
        // Mutex and condition variable to protect access to queue
        std::mutex m_mtx;
        std::condition_variable m_condVar;
        std::queue<std::string> m_queue;
        // The background thread;
        std::thread m_thread;   // Todo: 推荐使用boost并行队列，不需要锁就可以保证线程并发安全访问
        // Enable loging to file
        Level m_defLevel {Level::DEBUG};
        bool m_toFile {false};
        std::ofstream m_logFile;
};

Logger::Logger()
{
    // 启动后台thread
    m_thread = std::thread {&Logger::processEntries, this};
}

Logger::~Logger()
{
    {
        std::unique_lock lock {m_mtx};
        m_exit = true;
    }
    // Notify condition variable to wait up thread
    m_condVar.notify_all();
    // Wait until thread is shut down. This should be outside the above code block because
    // the lock must be released before calling join()
    m_thread.join(); // 为何在这里调用join()？？？
}

template <typename... Args>
void Logger::log(const int line, const char* source, Level level, const char* message, Args... args)
{ // 目前可变长度参数args没有使用，如何扩展？？？
    const char* levelString = enum2String[int(level)];
    time_t current;
    time(&current);
    struct tm* timeinfo {localtime(&current)};
    std::string entry = std::format("[{}]\t{} at line {} in file {} at {}", 
        levelString, message, line, source, asctime(timeinfo));

    // 锁住m_mtx，写入记录
    std::unique_lock lock {m_mtx};
    m_queue.push(std::move(entry));
    // Notify condition variable to wake up the background thread
    m_condVar.notify_all();
}

template <typename... Args>
void Logger::logTrace(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::TRACE, message, args...);
}
template <typename... Args>
void Logger::logDebug(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::DEBUG, message, args...);
}
template <typename... Args>
void Logger::logInfo(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::INFO, message, args...);
}
template <typename... Args>
void Logger::logWarn(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::WARN, message, args...);
}
template <typename... Args>
void Logger::logError(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::ERROR, message, args...);
}
template <typename... Args>
void Logger::logFatal(const int line, const char* source, const char* message, Args... args)
{
    log(line, source, Level::FATAL, message, args...);
}

void Logger::setDefaultLevel(Level level)
{
    m_defLevel = level; // Todo: add protection
}

void Logger::enableLogToFile(const char* fname="log.txt")
{
    // Open log file
    m_logFile = std::ofstream {fname};
    if (m_logFile.fail()) {
        std::cerr << "Failed to open log file " << fname << std::endl;
        return;
    }
    m_toFile = true;    // Require protection???
}

void Logger::processEntries()
{
    // Create a lock for m_mtx, but do not yet acquire a lock on it
    std::unique_lock lock {m_mtx, std::defer_lock};
    // Starting processing loop
    while (true) {
        lock.lock();
        
        if (!m_exit) { // Only wait for notification if we don't have to exit
            // Wait for a notification
            m_condVar.wait(lock);
        } else {
            // We have to exit, process the remaining entries in the queue
            processEntriesHelper(m_queue);
            break;
        }

        // Condition variable notified, so something might be in the queue
        // While we still have the lock, swap the contents of the current queue with an empty local queue
        // on the stack.
        std::queue<std::string> localQueue;
        localQueue.swap(m_queue);

        // Release the lock so that writing threads not blocked while processing the local queue
        lock.unlock();

        // Process the local queue
        processEntriesHelper(localQueue);
    }
}

void Logger::processEntriesHelper(std::queue<std::string>& queue) const
{
    // if (!m_toFile) {
    //     using ofs = std::cout;
    // } else {
    //     using ofs = m_logFile;
    // }
    while (!queue.empty()) {
        std::cout << queue.front() << "\n";
        queue.pop();
    }
}

}
