#ifndef __EMPLOYEERECORDSYS_H__
#define __EMPLOYEERECORDSYS_H__
#include <string>

namespace Records {

const int defaultRaiseAmount {500};
const int defaultSalary {5000};

class Employee {
    public:
        Employee(const std::string& fname, const std::string& lname);
        void promote(int raiseAmount=defaultRaiseAmount);
        void demote(int demeritAmount=defaultRaiseAmount);
        void hire(); // Hires or rehires the employee
        void fire(); // Dimiss the employee
        void display() const; // Display emploee info
        // Getter and setter
        void setFirstName(const std::string& fname);
        const std::string& getFirstName() const;
        void setLastName(const std::string& lname);
        const std::string& getLastName() const;
        void setEmployeeNumber(int employeeNumber);
        int getEmployeeNumber() const;
        void setSalary(int newSalary);
        int getSalary() const;
        bool isHired() const;
    private:
        std::string m_fname, m_lname;
        int m_employeNumber {-1};
        int m_salary {defaultSalary};
        bool m_hired {false};
};

}
#endif // __EMPLOYEERECORDSYS_H__