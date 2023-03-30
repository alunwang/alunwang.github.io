#include <iostream>
#include "database.h"

using namespace std;
using namespace Records;

void test_database()
{
    Database myDB;
    Employee& emp1 {myDB.addEmployee("Greg", "Wallis")};
    emp1.fire();

    Employee& emp2 {myDB.addEmployee("Marc", "White")};
    emp1.setSalary(100'000);

    Employee& emp3 {myDB.addEmployee("John", "Doe")};
    emp3.setSalary(10'000);
    emp3.promote();

    Employee& emp4 {myDB.addEmployee("Alan", "Wang")};
    emp4.setSalary(200'000);

    cout << "All employees: \n";
    myDB.displayAll();
    cout << endl << endl;

    cout << "Current employees: \n";
    myDB.displayCurrent();
    cout << endl << endl;
    
    cout << "Former employees: \n";
    myDB.displayFormer();
}