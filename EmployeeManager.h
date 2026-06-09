#pragma once

#include "Employee.h"
#include "Manager.h"
#include "Technician.h"
#include "Salesman.h"
#include <QVector>

class EmployeeManager {
public:
    EmployeeManager();
    ~EmployeeManager();

    bool loadFromFile(const QString& filename);
    bool saveToFile(const QString& filename) const;

    bool addEmployee(Employee* e);
    void removeEmployee(int index);
    bool updateEmployee(int index, Employee* newData);
    Employee* employeeAt(int index) const;
    int count() const;
    void clear();
    QVector<Employee*>& employees();

private:
    QVector<Employee*> m_employees;
};