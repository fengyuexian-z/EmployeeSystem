#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager :public Employee {
public:
    Manager();
    double bonus;

    int type() const override;
    double calcSalary() const override;
    QString displayInfo() const override;
    void writeToStream(QDataStream& out) const override;
    void readFromStream(QDataStream& in) override;
};

#endif 
