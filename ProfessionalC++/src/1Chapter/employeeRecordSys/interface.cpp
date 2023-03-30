#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include "employeeRecord.h"
#include "database.h"
#include "employeeTest.h"
#include "databaseTest.h"

using namespace std;
using namespace Records;

int displayMenu()
{
    int selection;
    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-------------------" << endl;
    cout << "1) Hire an employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    cin >> selection;
    while (cin.fail()) { // Bug: could not detect the input of 1.x/0.x error
        cout << "Error input, you need to input an integer." << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "---> ";
        cin >> selection;
    }

    return selection;
}

void doHire(Database& db)
{
    string fname, lname;
    cout << "First name? ";
    cin >> fname;

    cout << "Last name? ";
    cin >> lname;

    auto& employee {db.addEmployee(fname, lname)};
    cout << fmt::v9::format("Hired employee {} {} with employee number {}.",
        fname, lname, employee.getEmployeeNumber()) << endl;
}

void doFire(Database& db)
{
    int employeeNumber;
    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        auto& emp {db.getEmployee(employeeNumber)};
        emp.fire();
        cout << fmt::v9::format("Employee {} terminated.", employeeNumber) << endl;
    } catch (const logic_error& e) {
        cerr << fmt::v9::format("Unable to terminate employee: {}", e.what()) << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    cout << "Employee number? ";
    cin >> employeeNumber;

    int raiseAmount;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        auto& emp {db.getEmployee(employeeNumber)};
        emp.promote(raiseAmount);
    } catch (const logic_error& e) {
        cerr << fmt::v9::format("Unable to promote employee: {}", e.what()) << endl;
    }
}

int main(int argc, char* argv[])
{
    Database employeeDB;
    bool done {false};

    while (!done) {
        int selection {displayMenu()};
        switch(selection) {
        case 0:
            done = true;
            break;
        case 1:
            doHire(employeeDB);
            break;
        case 2:
            doFire(employeeDB);
            break;
        case 3:
            doPromote(employeeDB);
            break;
        case 4:
            employeeDB.displayAll();
            break;
        case 5:
            employeeDB.displayCurrent();
            break;
        case 6:
            employeeDB.displayFormer();
            break;
        default:
            cerr << "Unkown command." << endl;
            break;
        }
    }

    // test_employeeRecord();
    // test_database();

}