#include <iostream>
#include "employeeRecord.h"

using namespace std;
using namespace Records;

void test_employeeRecord()
{
    cout << "testing the Employee class...\n";

    Employee emp {"Jane", "Doe"};
    emp.setFirstName("John");
    emp.setLastName("Doe");
    emp.setEmployeeNumber(71);
    emp.setSalary(50'000);
    emp.promote();
    emp.promote(50);
    emp.hire();
    emp.display();
}