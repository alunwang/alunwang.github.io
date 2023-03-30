#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <string>
#include <cstdlib>

#include "logger.h"

using namespace std;


namespace logspace
{

Logger::Logger()
{
    // 产生后台thread
    m_thread = thread {&Logger::processEntries, this};
}

Logger::~Logger()
{
    {
        unique_lock lock {m_mutex};
        // Gracefully shutdown the thread by setting m_exit to true
        m_exit = true;
    }
    // Notify condition variable to wake up thread
    m_condVar.notify_all();
    // Wait until thread is shut down. This should be outside the above code block
    // because the lock must be released before calling join()!???
    m_thread.join();
}
void Logger::log(string entry)
{
    // Lock the queue, then add entry to it
    unique_lock lock {m_mutex};
    m_queue.push(move(entry));
    // Notify condition varriable to wake up thread
    m_condVar.notify_all();
}

void Logger::processEntries()
{
    // Open log file
    ofstream logFile {"log.txt"};
    if (logFile.fail()) {
        cerr << "Failed to open log file." << endl;
        return;
    }

    // Create a lock for m_mutex, but do not yet acquire a lock on it
    unique_lock lock {m_mutex, defer_lock};
    // Start processing loop
    while (true) {
        lock.lock();
        if (!m_exit) {
            // Wait for a notification
            m_condVar.wait(lock);
        } else {
            // Condition variable is notified, so something is in the queue

            // 采用缓冲：定义一个临时缓冲，让它与原来的缓冲swap（指针交换，速度快）
            // While we still have the lock, swap the contents of the current queue
            // with en empty local queue on the stack
            queue<string> localQueue;
            localQueue.swap(m_queue);

            // Now that all entries have been moved from current queue to the local queue,
            // we can release the lock so that other threads are not blocked while we process the entries
            lock.unlock();

            // 此后，写入queue和写入文件各自独立：
            // 1. 前台多thread写入queue
            // 2. 后台thread从localqueue读取写入文件
            // Process the entries in the local queue on the stack. This happen after having
            // released the lock.
            processEntriesHelper(localQueue, logFile);
            break;
        }
    }
}

void Logger::processEntriesHelper(queue<string>& queue, ofstream& ofs) const
{
    while (!queue.empty()) {
        ofs << queue.front() << endl;
        queue.pop();
    }
}

}


void logSomeMessages(int id, logspace::Logger& logger)
{
    char buf[30];
    for (int i {0}; i<10; ++i) {
        snprintf(buf, 30, "Log entry %d from thread %d", i, id);
        logger.log(string(buf));
    }
}

int main()
{
    logspace::Logger logger;
    vector<thread> threads;

    // Create a few threads all working with the same Logger instance
    for (int i {0}; i<10; ++i) {
        threads.emplace_back(logSomeMessages, i, ref(logger));
    }
    // Wait for threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}