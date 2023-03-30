#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <vector>
#include "employeeRecord.h"

namespace Records {

const int firstEmployeeNumber {1'000};

class Database {
    public:
        Employee& addEmployee(const std::string& fname, const std::string& lname);
        Employee& getEmployee(int employeeNumber);
        Employee& getEmployee(const std::string& fname, const std::string& lname);
        void displayAll() const;
        void displayCurrent() const;
        void displayFormer() const;
    private:
        std::vector<Employee> m_employees;
        int m_nextEmployeeNumber {firstEmployeeNumber};
};

}
#endif //__DATABASE_H__