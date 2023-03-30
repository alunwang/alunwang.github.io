#pragma once    // 保证头文件只被编译一次，防止头文件被重复引用。

#include <fstream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <string>
#include <cstdlib>

namespace logspace
{

enum class LogLevel {
    TRACE, DEBUG, INFO, WARN, ERROR, FATAL
};

class Logger {
    public:
        // Start a background thread writing log entries to file
        Logger();
        // Gracefully shutdown  background thread
        virtual ~Logger();
        // Prevent copy construction and assignment
        Logger(const Logger& src) = delete;
        Logger& operator=(const Logger& rhs) = delete;
        // Add log entry to the queue
        void log(std::string entry);
    private:
        // The function running in the background thread
        void processEntries();
        // Helper function to process a queue of entries
        void processEntriesHelper(std::queue<std::string>& queue,
            std::ofstream& ofs) const;
        // Mutex and condition variables to protect access to the queue
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        // 存储日志记录的queue，多线程共享
        std::queue<std::string> m_queue;
        // 后台thread，它独自负责将该class的queue里日志记录写入文件
        std::thread m_thread;
        // Boolean telling the background thread to terminate
        bool m_exit {false};
    private:
        static LogLevel m_defLevel;
};
LogLevel Logger::m_defLevel = LogLevel::INFO;

}