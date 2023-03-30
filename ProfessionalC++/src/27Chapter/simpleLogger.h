#pragma once

#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <ctime>


namespace logging
{

enum class Level {
    TRACE=0, DEBUG, INFO, WARN, ERROR, FATAL
};

const char* enum2String[] = { // 用于enum映射为相应字符串
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

/*
 * 全部使用静态成员来实现
 */
class Logger {
    public:
        static void enableLogToFile()
        {
            if (m_file) {
                fclose(m_file);
            }
            m_file = fopen("log.txt", "a");
            if (!m_file) {
                printf("Cannot open the file.\n");
                abort();
            }
            m_toFile = true; // Todo: add protection
        }
        static void enableLogToFile(const char* fname)
        {
            if (m_file) {
                fclose(m_file);
            }
            m_file = fopen(fname, "a");
            if (!m_file) {
                printf("Cannot open file %s.\n", fname);
                abort();
            }
            m_toFile = true;
        }
        static void disableLogToFile()
        {
            m_toFile = false;
            fclose(m_file);
        }
        static void setDefaultLevel(Level level)
        {
            m_defLevel = level;
        }
        template <typename... Args>
        static void logTrace(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::TRACE, message, args...);
        }
        template <typename... Args>
        static void logDebug(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::DEBUG, message, args...);
        }
        template <typename... Args>
        static void logInfo(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::INFO, message, args...);
        }
        template <typename... Args>
        static void logWarn(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::WARN, message, args...);
        }
        template <typename... Args>
        static void logError(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::ERROR, message, args...);
        }
        template <typename... Args>
        static void logFatal(const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            log(Level::FATAL, message, args...);
        }

    private:
        template <typename... Args>
        static void log(Level level, const char* message, Args... args)
        {
            const char* levelString = enum2String[int(level)];
            char buf[20];
            snprintf(buf, 20, "[%s]\t", levelString); // 加上[]和制表符
            time_t current;
            time(&current);
            struct tm* timeinfo {localtime(&current)};
            if (m_defLevel <= level) {
                if (!m_toFile) {
                    printf("%s", buf);
                    printf(message, args...);
                    printf(" - %s", asctime(timeinfo));
                    // printf("\n"); // asctime()加了'\n'，所以此行不再需要
                } else {
                    fprintf(m_file, "%s", buf);
                    fprintf(m_file, message, args...);
                    fprintf(m_file, " - %s", asctime(timeinfo));
                    // fprintf(m_file, "\n");
                }
            }
        }
    private:
        static Level m_defLevel;
        static std::mutex m_mtx;
        static bool m_toFile;
        static FILE* m_file;
};
Level Logger::m_defLevel {Level::INFO};
std::mutex Logger::m_mtx {};
bool Logger::m_toFile {false};
FILE* Logger::m_file {nullptr};


/*
 * 使用singleton设计模式来实现
 */
class SingletonLogger {
    public:
        SingletonLogger(const SingletonLogger& slogger) = delete;
        SingletonLogger& operator=(const SingletonLogger& slogger) = delete;
    public:
        static void enableLogToFile(const char* fname="log.txt")
        {
            if (getLogger().m_file) {
                fclose(getLogger().m_file);
            }
            getLogger().m_file = fopen(fname, "a");
            if (!(getLogger().m_file)) {
                printf("Cannot open file %s.\n", fname);
                abort();
            }
            getLogger().m_toFile = true; // Todo: add protection
        }
        static void setDefaultLevel(Level level)
        {
            getLogger().m_defLevel = level; // Todo: add protection
        }
        template <typename... Args>
        static void logTrace(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::TRACE, message, args...);
        }
        template <typename... Args>
        static void logDebug(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::DEBUG, message, args...);
        }
        template <typename... Args>
        static void logInfo(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::INFO, message, args...);
        }
        template <typename... Args>
        static void logWarn(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::WARN, message, args...);
        }
        template <typename... Args>
        static void logError(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::ERROR, message, args...);
        }
        template <typename... Args>
        static void logFatal(const int line, const char* source, const char* message, Args... args)
        {
            std::unique_lock<std::mutex> lock(getLogger().m_mtx);
            getLogger().log(line, source, Level::FATAL, message, args...);
        }
    private:
        SingletonLogger()
        {
        }
        ~SingletonLogger()
        {
            if (m_file) {
                fclose(m_file);
            }
        }
        // 当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。
        // 这样保证了并发线程在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性。
        // 源自：https://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html
        static SingletonLogger& getLogger()
        {
            static SingletonLogger instance;
            return instance;
        }
        template <typename... Args>
        void log(const int line, const char* source, Level level, const char* message, Args... args)
        {
            const char* levelString = enum2String[int(level)];
            char buf[20];
            snprintf(buf, 20, "[%s]\t", levelString); // 加上[]和制表符
            time_t current;
            time(&current);
            struct tm* timeinfo {localtime(&current)};
            if (m_defLevel <= level) {
                if (!m_toFile) { // 写入标准输出
                    printf("%s", buf);
                    printf(message, args...);
                    printf(" - at line %d in file %s", line, source);
                    printf(" - %s", asctime(timeinfo));
                } else { // 写入日志文件
                    fprintf(m_file, "%s", buf);
                    fprintf(m_file, message, args...);
                    fprintf(m_file, "- at line %d in file %s", line, source);
                    fprintf(m_file, " - %s", asctime(timeinfo));
                }
            }
        }
    private:
        Level m_defLevel {Level::INFO};
        std::mutex m_mtx {};
        bool m_toFile {false};
        FILE* m_file {nullptr};
};

#define LOG_TRACE(message, ...) (logging::SingletonLogger::logTrace(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_DEBUG(message, ...) (logging::SingletonLogger::logDebug(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_INFO(message, ...) (logging::SingletonLogger::logInfo(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_WARN(message, ...) (logging::SingletonLogger::logWarn(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_ERROR(message, ...) (logging::SingletonLogger::logError(__LINE__, __FILE__, message, __VA_ARGS__))
#define LOG_FATAL(message, ...) (logging::SingletonLogger::logFatal(__LINE__, __FILE__, message, __VA_ARGS__))

}










