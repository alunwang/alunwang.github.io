#include <string>
#include <vector>
#include "roundRobin.h"

using namespace std;

class Process final {
    public:
        explicit Process(string name) : m_name {move(name)} {}
        void doWorkDuringTimeSlice()
        {
            cout << "Process " << m_name << " performing work during time slice." << endl;
        }
        bool operator==(const Process&) const = default; // = default since C++20

    private:
        string m_name;
};

class Scheduler final {
    public:
        explicit Scheduler(const vector<Process>& processes)
        {
            for (auto& process : processes) {
                m_processes.add(Process);
            }
        }
        void scheduleTimeSlice()
        {
            try {
                m_processes.getNext().doWorkDuringTimeSlice();
            } catch (const out_of_range&) {
                cerr << "No more processes to schedule." << endl;
            }
        }
        void removeProcess(const Process& process)
        {
            m_processes.remove(process);
        }
    private:
        RoundRobin<Process> m_processes;
};


int main()
{
    vector processes {Process {"1"}, Process {"2"}, Process {"3"}};

    Scheduler scheduler {processes};
    for (size_t {0}; i<4; i++) {
        scheduler.scheduleTimeSlice();
    }

    scheduler.removeProcess(processes[1]);
    cout << "Removed second process" << endl;
    
    for (size_t i {0}; i<4; ++i) {
        scheduler.scheduleTimeSlice();
    }
}