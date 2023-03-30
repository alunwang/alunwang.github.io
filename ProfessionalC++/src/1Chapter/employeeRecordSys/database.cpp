#include <stdexcept>
#include "database.h"

using namespace std;

namespace Records {

Employee& Database::addEmployee(const string& fname, const string& lname)
{
    Employee emp {fname, lname};
    emp.setEmployeeNumber(m_nextEmployeeNumber++);
    emp.hire();
    m_employees.push_back(emp);
    return m_employees.back();
}

Employee& Database::getEmployee(int employeeNumber)
{
    for (auto& employee : m_employees) {
        if (employee.getEmployeeNumber() == employeeNumber) {
            return employee;
        }
    }
    throw logic_error {"No employee found."};
}

Employee& Database::getEmployee(const string& fname, const string& lname)
{
    for (auto& emp : m_employees) {
        if ((emp.getFirstName() == fname) && (emp.getLastName() == lname)) {
            return emp;
        }
    }
    throw logic_error {"No employee found."};
}

void Database::displayAll() const
{
    for (const auto& emp : m_employees) {
        emp.display();
    }
}

void Database::displayCurrent() const
{
    for (const auto& emp : m_employees) {
        if (emp.isHired()) {
            emp.display();
        }
    }
}

void Database::displayFormer() const
{
    for (const auto& emp : m_employees) {
        if (!emp.isHired()) {
            emp.display();
        }
    }
}

}